import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  bool isPumpOn = true;

  double ph = 0;
  double ec = 0;
  double waterTemp = 0;
  double humidity = 0;
  double airTemp = 0;
  bool smoke = false;

  final dbRef = FirebaseDatabase.instance.ref();

  @override
  void initState() {
    super.initState();
    dbRef.child('motor/status').onValue.listen((event) {
      final value = event.snapshot.value;

      if (value != null) {
        setState(() {
          isPumpOn = value as bool;
        });
      }
    });
    dbRef.child('sensors').onValue.listen((event) {
      final data = event.snapshot.value as Map? ?? {};
      setState(() {
        ph = data['ph']?.toDouble() ?? 0;
        ec = data['ec']?.toDouble() ?? 0;
        waterTemp = data['waterTemp']?.toDouble() ?? 0;
        humidity = data['humidity']?.toDouble() ?? 0;
        airTemp = data['airTemp']?.toDouble() ?? 0;
        smoke = data['smoke'] ?? false;
      });
      _autoControlMotor();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      body: SafeArea(
        child: SingleChildScrollView(
          child: Padding(
            padding: const EdgeInsets.symmetric(horizontal: 30, vertical: 10),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                const SizedBox(height: 10),

                /// Title
                Text(
                  "Water Pump Status: ${isPumpOn ? "ON" : "OFF"}",
                  style: const TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.w500,
                  ),
                ),

                const SizedBox(height: 15),

                /// Pump Card
                Container(
                  padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
                  decoration: BoxDecoration(
                    color: const Color(0xFFDADADA),
                    borderRadius: BorderRadius.circular(20),
                  ),
                  child: Column(
                    children: [
                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          const Text(
                            "Water Pump",
                            style: TextStyle(fontSize: 15),
                          ),
                          Switch(
                            value: isPumpOn,
                            inactiveThumbColor: Colors.white,
                            inactiveTrackColor: Colors.grey,
                            activeThumbColor: Colors.white,
                            activeTrackColor: Colors.green,
                            onChanged: (val) {
                              setState(() {
                                isPumpOn = val;
                              });
                              dbRef.child('motor').update({
                                'status':val,
                              });
                            },
                          )
                        ],
                      ),
                    ],
                  ),
                ),

                const SizedBox(height: 5),
                Row(
                  children: const [
                    Icon(Icons.info_outline, size: 14),
                    SizedBox(width: 5),
                    Text(
                      "Manually turn on the pump",
                      style: TextStyle(fontSize: 12),
                    ),
                  ],
                ),

                const SizedBox(height: 15),

                /// Sensor Card
                Container(
                  padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 14),
                  decoration: BoxDecoration(
                    color: const Color(0xFFDADADA),
                    borderRadius: BorderRadius.circular(20),
                  ),
                  child: Column(
                    children: [
                      _rowWithDivider("Smoke Detected", smoke ? "Yes" : "No"),

                      _progressWithDivider("pH", ph / 14, ph.toStringAsFixed(1)),

                      _progressWithDivider(
                          "Electrical Conductivity", ec / 20, ec.toStringAsFixed(1)),

                      _rowWithDivider("Water Temperature", "${waterTemp.toStringAsFixed(1)} °C"),

                      // _rowWithDivider(
                      //     "Air Temperature", airTemp > 35 ? "High" : airTemp < 20 ? "Low" : "Perfect"),

                      _rowWithDivider("Air Temperature", "${airTemp.toStringAsFixed(1)} °C"),

                      // _rowNoDivider(
                      //     "Humidity", humidity > 70 ? "High" : humidity < 30 ? "Low" : "Perfect"),

                      _rowNoDivider(
                          "Humidity", "${humidity.toStringAsFixed(1)} %"),
                    ],
                  ),
                ),

                const SizedBox(height: 8),

                /// Footer
                Row(
                  children: const [
                    Icon(Icons.info_outline, size: 14),
                    SizedBox(width: 5),
                    Text(
                      "Sensor Data",
                      style: TextStyle(fontSize: 12),
                    )
                  ],
                ),

                const SizedBox(height: 15),

                Container(
                  padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 14),
                  decoration: BoxDecoration(
                    color: const Color(0xFFDADADA),
                    borderRadius: BorderRadius.circular(20),
                  ),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      if (smoke)
                        const _RecommendationText("Smoke is detected. Find the cause."),
                      if (ph < 6.5)
                        const _RecommendationText("Water pH is LOW. Add alkaline solution."),

                      if (ph > 8.5)
                        const _RecommendationText("Water pH is HIGH. Add acidic solution."),

                      if (ec < 5)
                        const _RecommendationText("Electrical Conductivity is LOW."),

                      if (ec > 15)
                        const _RecommendationText("Electrical Conductivity is HIGH."),

                      if (waterTemp < 20)
                        const _RecommendationText("Water temperature is LOW."),

                      if (waterTemp > 35)
                        const _RecommendationText("Water temperature is HIGH."),

                      if (humidity < 30)
                        const _RecommendationText("Humidity is LOW."),

                      if (humidity > 70)
                        const _RecommendationText("Humidity is HIGH."),

                      if (!smoke && ph >= 6.5 && ph <= 8.5 && ec >= 5 && ec <= 15 && waterTemp >= 20 && waterTemp <= 35 && humidity >= 30 && humidity <= 70)
                        const _RecommendationText("Environment is safe."),
                    ],
                  ),
                ),

                const SizedBox(height: 8),

                Row(
                  children: const [
                    Icon(Icons.info_outline, size: 14),
                    SizedBox(width: 5),
                    Text(
                      "Recommendations",
                      style: TextStyle(fontSize: 12),
                    )
                  ],
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  /// Row with Divider
  Widget _rowWithDivider(String title, String value) {
    return Column(
      children: [
        _row(title, value),
        const SizedBox(height: 6),
        const Divider(thickness: 0.6, color: Colors.black54),
      ],
    );
  }

  /// Row without Divider (last element)
  Widget _rowNoDivider(String title, String value) {
    return _row(title, value);
  }

  /// Basic Row
  Widget _row(String title, String value) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Text(title, style: const TextStyle(fontSize: 13)),
        Text(value,
            style: const TextStyle(fontSize: 13, color: Colors.black54)),
      ],
    );
  }

  /// Progress + Divider
  Widget _progressWithDivider(String title, double value, String label) {
    return Column(
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Text(title, style: const TextStyle(fontSize: 13)),
            Text(label,
                style:
                const TextStyle(fontSize: 13, color: Colors.black54)),
          ],
        ),
        const SizedBox(height: 5),
        LinearProgressIndicator(
          value: value,
          minHeight: 4,
          backgroundColor: Colors.grey,
          color: Colors.blue,
        ),
        const SizedBox(height: 6),
        const Divider(thickness: 0.6, color: Colors.black54),
      ],
    );
  }

  void _autoControlMotor() {
    bool unsafe =
        smoke ||
        ph < 6.5 || ph > 8.5 ||
        ec < 5 || ec > 15 ||
        waterTemp < 20 || waterTemp > 35 ||
        humidity < 30 || humidity > 70 ||
        airTemp < 20 || airTemp > 35;

    if (unsafe && isPumpOn) {
      // Turn OFF motor
      dbRef.child('motor').update({'status': false});
    }

    if (!unsafe && !isPumpOn) {
      // Optional: Turn ON automatically (you can remove if not needed)
      dbRef.child('motor').update({'status': true});
    }
  }
}

class _RecommendationText extends StatelessWidget {
  final String text;

  const _RecommendationText(this.text);

  @override
  Widget build(BuildContext context) {
    return Row(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Text("• ", style: TextStyle(fontSize: 13)),
        Expanded(
          child: Text(
            text,
            style: const TextStyle(
              fontSize: 13,
              color: Colors.black87,
            ),
          ),
        ),
      ],
    );
  }
}
