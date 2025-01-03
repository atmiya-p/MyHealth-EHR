# Electronic Health Record (EHR) Management System

# Project Overview

After our Requirements Gathering and Analysis, we realized that a non-trivial, real-world problem that needs to be addressed is the lack of efficient and secure management of Electronic Health Records. There is a need for a system to be implemented where patients are able to access their records.

This desktop application was built to solve this problem. It has seperate functionality for Doctors and Patients, which includes a secure login and signup process, management of patient records, along with the plan of having a complete appointment booking system.

The application uses SQLite as the database backend and is designed with a modular and maintainable architecture that ensures low coupling and high cohesion with the implementation of many Design Patterns.


## Project Features

### Doctor
* Sign Up - Can signup only if have the code "DOCTOR". This prevents anyone from just signing up as a doctor
* Login functionality
* Able to add, view, update patient records. Patient records include visit dates, doctor notes, and prescriptions given

### Patient
* Sign Up - Can signup only if a doctor has them added in their database. This prevents anyone from just signing up as a patient. The doctors username will be required to sign up which will be given by the doctor for them to sign up
* Login functionality
* Dashboard to view their personal health records

## Setup and Installation

### 1. Prerequisites
* Install the Qt Framework: Download and install Qt Creator from the official Qt website. Ensure you install the necessary Qt libraries for your platform (Windows, macOS, Linux).
* SQLite: SQLite is included with most Qt installations. Confirm that your Qt installation includes SQLite support.
* C++ Compiler: Ensure you have a compatible C++ compiler installed.

### 2. Build Instructions
Clone the Repository:
* git clone <repository-url>
* cd <repository-folder>

Open the Project in Qt Creator:
* Launch Qt Creator.
* Open the .pro file from the cloned repository.
* Configure Build Settings: [location-of-folder]/code/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug

* Build the Project: Click on the Build button or press Ctrl + B to compile the project.
* Ensure there are no errors during the build process.

* Run the Application: Once the build is successful, click the Run button or press Ctrl + R to launch the application.


## Technologies Used
* Programming Language: C++
* Database: SQLite
* IDE: Qt Creator
* Version Control: Git

## About Us
* This project was created by Atmiya Patel and Ben Santhosh for CS3307A at Western University.
