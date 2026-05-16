# AgriMon - Agricultural IoT Monitoring App

A Flutter-based IoT monitoring application designed for agricultural automation and sensor data tracking. AgriMon provides real-time monitoring of agricultural sensors and control of water pump systems for intelligent irrigation management.

## 📱 Features

- **Splash Screen**: Animated splash screen with Lottie animations on app startup
- **Sensor Monitoring**: Real-time tracking of:
  - Temperature
  - Humidity
  - Pressure
  - NH3 (Ammonia) levels
  - LPG (Liquefied Petroleum Gas) levels
  - CH4 (Methane) levels
- **Water Pump Control**: Manual on/off toggle for water pump management
- **Beautiful UI**: Clean, modern interface using Material Design
- **Custom Fonts**: Google Fonts integration for enhanced typography
- **Local Notifications**: Push notification support via flutter_local_notifications

## 🛠️ Prerequisites

Before you begin, ensure you have the following installed:
- **Flutter SDK**: Version 3.9.2 or higher
- **Dart SDK**: Included with Flutter
- **Android Studio** (for Android development)
- **Xcode** (for iOS development on macOS)
- **Git**: For version control

## 📦 Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/agri_app.git
cd agri_app
```

### 2. Get Flutter Dependencies
```bash
flutter pub get
```

### 3. Run the Application
```bash
flutter run
```

To target a specific platform:
```bash
flutter run -d android    # For Android devices
flutter run -d ios        # For iOS devices (macOS only)
flutter run -d chrome     # For web browsers
```

## 📁 Project Structure

```
agri_app/
├── lib/
│   ├── main.dart              # App entry point
│   ├── start.dart             # Splash screen with animations
│   ├── home.dart              # Home page with pump control
│   ├── sensor_data.dart       # Sensor data model
├── assets/
│   ├── images/                # Image assets including agrimon.json
│   └── videos/                # Video assets
├── android/                   # Android-specific code
├── ios/                       # iOS-specific code
├── web/                       # Web build files
├── windows/                   # Windows build files
├── linux/                     # Linux build files
├── macos/                     # macOS build files
├── pubspec.yaml               # Project configuration and dependencies
└── README.md                  # This file
```

## 🔧 Dependencies

Key packages used in this project:

```yaml
dependencies:
  flutter:                           # Flutter framework
  cupertino_icons: ^1.0.8           # iOS-style icons
  google_fonts: ^8.1.0              # Google Fonts integration
  lottie: ^3.3.3                    # Lottie animations
  flutter_local_notifications: ^19.4.0  # Local push notifications
```

For development:
```yaml
dev_dependencies:
  flutter_test: ^0.0.0              # Flutter testing framework
  flutter_lints: ^5.0.0             # Linting rules
```

## 🚀 Usage

### Starting the App
1. Launch the app on your device
2. View the animated splash screen (AgriMon branding)
3. Access the home page with:
   - Water pump status and control
   - Real-time sensor data monitoring
   - Manual pump toggle switch

### Water Pump Control
- Use the toggle switch to turn the water pump ON/OFF
- Provides manual irrigation control
- Status is displayed at the top of the home page

### Sensor Data Integration
The app integrates with IoT sensors via API endpoints to fetch:
- Real-time environmental data
- Historical sensor readings
- Data visualization

## 🏗️ Building for Production

### Android
```bash
flutter build apk --release
```

### iOS
```bash
flutter build ios --release
```

### Web
```bash
flutter build web --release
```

## 🐛 Troubleshooting

### Common Issues

**Lottie animations not displaying:**
- Ensure `agrimon.json` exists in `assets/images/`
- Check that assets are properly declared in `pubspec.yaml`

**Sensor data not loading:**
- Verify API endpoint connectivity
- Check network permissions in platform-specific settings
- Ensure proper sensor hardware integration

**Build errors:**
- Run `flutter clean` to clear build artifacts
- Run `flutter pub get` to reinstall dependencies
- Check Flutter and Dart versions compatibility

## 📋 System Requirements

- **Minimum SDK Version**: Android 5.0 (API 21) or iOS 11.0
- **Target SDK Version**: Latest stable versions
- **RAM**: Minimum 2GB (4GB recommended)
- **Storage**: Minimum 100MB free space

## 🔐 API Integration

This app is designed to work with IoT platforms that provide sensor data APIs. The `SensorData` class handles JSON parsing from API responses with fields for:
- field1: Temperature
- field2: Humidity
- field3: Pressure
- field4: NH3 levels
- field5: LPG levels
- field6: CH4 levels

## 📝 License

This project is provided as-is. Please add your preferred license (MIT, GPL, Apache, etc.) if planning to open-source.

## 👥 Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📞 Contact

For questions or support:
- Create an issue in the repository
- Contact the project maintainer
- Check the [Flutter documentation](https://docs.flutter.dev)

## 🔗 Useful Resources

- [Flutter Documentation](https://flutter.dev/docs)
- [Dart Language Guide](https://dart.dev)
- [Material Design Guidelines](https://material.io/design)
- [Flutter Packages](https://pub.dev)

---

**Version**: 1.0.0  
**Last Updated**: 2026  
**Status**: Active Development
