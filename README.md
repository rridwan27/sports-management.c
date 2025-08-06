# ⚽ Soccer Management System

A comprehensive console-based soccer management system written in C that allows administrators, coaches, and players to manage teams, matches, and player information efficiently.

## 📋 Table of Contents

- [Features](#-features)
- [System Requirements](#-system-requirements)
- [Installation](#-installation)
- [Getting Started](#-getting-started)
- [User Roles](#-user-roles)
- [File Structure](#-file-structure)
- [Usage Guide](#-usage-guide)
- [Screenshots](#-screenshots)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features

### 🔐 Authentication System

- **User Registration**: New users can register as Coach or Player
- **Secure Login**: Username and password authentication
- **Role-based Access**: Different permissions for Admin, Coach, and Player

### 👨‍💼 Admin Features

- ✅ Approve team registration requests
- 📅 Schedule matches between teams
- 📊 Enter and update match results
- 📈 View comprehensive reports (teams, players, matches)

### 👨‍🏫 Coach Features

- 🏆 Create team registration requests
- 👥 Add players to their approved team
- 👀 View team roster and player details
- 📋 View match schedules

### ⚽ Player Features

- 👤 View personal profile information
- 🏃‍♂️ View team information and teammates
- 📅 View upcoming match schedules

## 🖥️ System Requirements

- **Operating System**: Windows, macOS, or Linux
- **Compiler**: GCC or any C compiler
- **Memory**: Minimal requirements (< 1MB)
- **Storage**: < 10MB for program and data files

## 🚀 Installation

### Step 1: Run

```bash
gcc sports.c -o sports
./sports
```

### Step 2: Compile the Program

```bash
# Using GCC
gcc -o soccer_management soccer_management.c

# Or using any C compiler
cc -o soccer_management soccer_management.c
```

### Step 3: Run the Program

```bash
# On Windows
soccer_management.exe

# On macOS/Linux
./soccer_management
```

## 🎯 Getting Started

### First Time Setup

1. **Run the Program**: The system automatically creates all necessary data files
2. **Default Admin Account**:
   - Username: `admin`
   - Password: `admin123`
3. **Login as Admin**: Use the default credentials to access admin features

### Quick Start Guide

```
=== Soccer Management System ===

=== Main Menu ===
1. Login
2. Register
3. Exit
Enter your choice: 1

=== Login ===
Username: admin
Password: admin123

=== Admin Menu ===
1. Approve Teams
2. Schedule Match
3. Enter Match Results
4. View Reports
5. Logout
```

## 👥 User Roles

### 🛡️ Administrator

- **Full System Access**: Complete control over the system
- **Team Management**: Approve or reject team requests
- **Match Control**: Schedule matches and enter results
- **System Oversight**: View all reports and statistics

### 👨‍🏫 Coach

- **Team Creation**: Submit team registration requests
- **Player Management**: Add players to approved teams
- **Team Oversight**: Monitor team roster and match schedule
- **Limited Access**: Cannot modify other teams or system settings

### ⚽ Player

- **Personal Info**: View own profile and statistics
- **Team Details**: See team information and teammates
- **Match Schedule**: Check upcoming games
- **Read-Only Access**: Cannot modify any system data

## 📁 File Structure

The system creates and manages the following data files:

```
soccer-management-system/
│
├── soccer_management.c          # Main source code
├── soccer_management.exe        # Compiled executable (after compilation)
├── README.md                   # This file
│
├── users.txt                   # User accounts (username,password,role)
├── teams.txt                   # Approved teams (name,coach,status)
├── team_requests.txt           # Pending team requests
├── players.txt                 # Player information
└── matches.txt                 # Match schedules and results
```

### File Formats

**users.txt**

```
admin,admin123,admin
john_coach,password123,coach
mike_player,mypass,player
```

**teams.txt**

```
Manchester United,john_coach,1
Arsenal,jane_coach,1
```

**players.txt**

```
1,Mike Johnson,25,Forward,Manchester United
2,Sarah Wilson,23,Midfielder,Arsenal
```

## 📖 Usage Guide

### For New Users

1. **Register an Account**

   ```
   Main Menu → 2. Register
   Enter username: your_username
   Enter password: your_password
   Confirm password: your_password
   Select role: 1 (Coach) or 2 (Player)
   ```

2. **Login to System**
   ```
   Main Menu → 1. Login
   Username: your_username
   Password: your_password
   ```

### For Coaches

1. **Create a Team**

   ```
   Coach Menu → 1. Create Team Request
   Enter team name: Your Team Name
   ```

2. **Add Players** (after team approval)
   ```
   Coach Menu → 2. Add Players
   Enter player details as prompted
   ```

### For Administrators

1. **Approve Teams**

   ```
   Admin Menu → 1. Approve Teams
   Select team number to approve
   ```

2. **Schedule Matches**
   ```
   Admin Menu → 2. Schedule Match
   Enter match details as prompted
   ```

## 📸 Screenshots

### Main Menu

```
=== Soccer Management System ===

=== Main Menu ===
1. Login
2. Register
3. Exit
Enter your choice:
```

### Admin Dashboard

```
=== Admin Menu ===
1. Approve Teams
2. Schedule Match
3. Enter Match Results
4. View Reports
5. Logout
Enter your choice:
```

### Team Registration

```
=== Create Team Request ===
Enter team name: Manchester City
Team request submitted for approval!
```
