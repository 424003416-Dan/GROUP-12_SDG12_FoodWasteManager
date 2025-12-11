# Food Waste Management System

# UN SDG Goal 12: Responsible Consumption and Production

Problem Statement: Food waste is a global issue where households and businesses lose track of inventory, forget expiry dates, and lack visibility into waste patterns. This system solves these problems by providing digital tracking, expiry alerts, and waste analytics to promote sustainable consumption habits and reduce food waste.

# Project Description

This is a C++ console application that implements three core Data Structures and Algorithms (DSA) to manage food inventory and reduce waste:

# Data Structures Used:

ARRAY - Static array for food inventory storage
Provides O(1) direct access when users select items by menu number. Arrays offer fast indexing and predictable memory usage for fixed-capacity storage (maximum 1000 items).

STACK - LIFO structure for alert management
The most recent alert is most relevant. Stack's Last-In-First-Out (LIFO) principle ensures new warnings (like "Milk expiring today!") appear before older notifications.

MERGE SORT - Sorting algorithm for waste analytics
Guarantees O(n log n) performance in all cases, unlike Quick Sort which can degrade to O(n²). Merge Sort is stable (preserves chronological order of equal items) and reliably meets the <1 second performance requirement.

# Installation/Setup
# Prerequisites:
• Code::Blocks IDE (recommended) OR any C++ compiler (g++, MinGW)
• Git for cloning the repository

# Steps to Setup:
1. Clone the repository:
• git clone https://github.com/424003416-Dan/GROUP-12_SDG12_FoodWasteManager/edit/main/README.md
• cd GROUP-12_SDG12_FoodWasteManager

2. Set up the project in Code::Blocks:
• Open Code::Blocks
• Create a new project or open the existing .cbp file if included
• Add all files from the CODE/ folder to your project

3. Prepare data files:
• Ensure the INPUT_DATA/ folder contains:
 - inventory.dat (100+ sample items)
 - waste.dat (50 waste logs)
 - alerts.dat (30 alert messages)

# Usage Instructions

Login Credentials:
Username: admin
Password: admin123

Main Menu Features:
1. VIEW FOOD INVENTORY
• Displays all food items with color-coded expiry status
• Shows quantity, category, and days remaining until expiry
• Red = Expired/Urgent, Yellow = Warning, Green = Good

2. CHECK EXPIRY ALERTS
• Shows items expiring within 7 days
• Displays recent system alerts (Stack LIFO display)
• Highlights urgent items (expiring in ≤3 days)

3. ADD FOOD ITEM
• Add new items to your digital pantry
• Enter name, quantity, expiry date (YYYY-MM-DD), and category
• System automatically calculates days to expiry

4. LOG WASTED FOOD
• Select an item from inventory and log waste quantity
• Choose reason: EXPIRED, OVERBOUGHT, SPOILED, or DAMAGED
• Automatically updates inventory and creates waste record

5. VIEW WASTE ANALYTICS
• Displays waste logs sorted by quantity (highest first)
• Uses Merge Sort algorithm for efficient sorting
• Shows total waste and patterns over time

6. PERFORMANCE TEST
• Tests all three DSA implementations
• Verifies system handles 100+ records in <1 second
• Shows individual operation timings

7. EXIT PROGRAM
• Saves all data to files automatically
• Ensures data persistence between sessions

Data Persistence:
• All data automatically saves to INPUT_DATA/ folder on exit
• Files use .dat binary format for efficient storage
• System loads previous data automatically on startup

# Contributors
Dan Edryl L. Caneo - BSIT 2nd Year Student

Primary Contributions:
• Designed and implemented all three DSA modules (Array, Stack, Merge Sort)
• Created file handling system for data persistence
• Developed user interface and menu system
• Implemented input validation and error handling
• Created test data and performance validation
• Prepared documentation and flowcharts

Modules Implemented:
• FoodArray Module - ARRAY data structure for inventory management
• AlertStack Module - STACK data structure for alert system
• MergeSort Module - MERGE SORT algorithm for waste analytics
• Utilities Module - Common helper functions and constants
• Main Controller - Program flow and menu system
