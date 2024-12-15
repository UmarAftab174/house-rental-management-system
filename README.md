# House Rental System

## Overview
The **House Rental System** is a console-based application developed as part of the **Computer Programming** course project for **Fall 2023**. The application provides an efficient way for users and administrators to manage house rentals. It leverages C++ for its implementation and uses the filesystem to handle data storage and retrieval.

## Features

### Admin Features
- **Admin Login & Registration**: Allows administrators to log in with existing credentials or register as a new admin.
- **House Management**:
  - Add new houses to the inventory.
  - View all houses in the inventory.
  - Delete houses from the inventory.

### User Features
- **User Login & Registration**: Users can either log in with their CNIC or register as new users.
- **House Search**:
  - Search for houses based on location or size.
  - View all available houses.
- **House Booking**:
  - Rent a house for a specified period.
  - Cancel a house reservation.

### Core Functionalities
- **Sequential ID Generation**: Automatically generates unique IDs for each house added to the inventory.
- **File-based Data Storage**: Stores admin, user, and house data in structured files within designated folders.

## Directory Structure
The application creates and organizes data files in the following structure:
```
./Data/
  |-- AdminData.txt       # Stores admin details
  |-- fileid.txt          # Stores the last assigned house ID
  |-- User/               # Stores user details (one file per user)
  |-- House/              # Stores house details (one file per house)
```

## How to Run
1. Compile the code using a C++ compiler (e.g., `g++`):
   ```
   g++ -o HouseRentalSystem main.cpp
   ```
2. Run the executable:
   ```
   ./HouseRentalSystem
   ```
3. Follow the prompts in the console to interact with the system.

## Dependencies
- C++17 or later (required for filesystem support).

## Input Validation
The system validates critical inputs to ensure data integrity:
- **CNIC**: Must be a 13-digit number.
- **Cell Number**: Must be an 11-digit number.
- **House ID and Number**: Automatically converted to uppercase for consistency.

## Example Usage
### Admin Workflow
1. Log in as an admin or register if no admin exists.
2. Add houses to the inventory by providing details like house number, location, size, and price.
3. View or delete houses from the inventory as needed.

### User Workflow
1. Log in as a user or register by providing CNIC and other details.
2. Search for houses using filters like location or size, or view all available houses.
3. Rent a house for a specific period or cancel an existing reservation.

## Limitations
- Passwords are stored in plain text, which poses a security risk.
- The system assumes a single admin user. Multi-admin functionality is not supported.
- Limited error handling for scenarios like simultaneous access or file corruption.

## Future Improvements
- Encrypt passwords for better security.
- Add support for multiple administrators.
- Enhance the user interface for better usability.
- Implement database integration for scalable data management.

## Acknowledgment
This project was developed as part of the **Computer Programming** course during Fall 2023 at Bahria University.
