## Build and Run
```bash
git clone --recursive https://github.com/GameDevCPP/bespokeassetmanagertool-jackdelahunt.git
```

```bash
cd bespokeassetmanagertool-jackdelahunt
```

```bash
.\vcpkg\bootstrap-vcpkg.bat
```

```bash
.\vcpkg\vcpkg.exe install sfml
```

```bash
.\vcpkg\vcpkg.exe install imgui
```

```bash
.\vcpkg\vcpkg.exe install imgui-sfml
```

```bash
.\vcpkg\vcpkg.exe install nlohmann-json
```
```bash
.\vcpkg\vcpkg.exe integrate install
```

```bash
.\vcpkg\vcpkg.exe integrate project
```

Visual studio should now be working out of the box