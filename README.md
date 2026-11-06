# BAGS & ACCESSORIES STORE
## E-Commerce Inventory & Search System

### Project Overview

The **Bags & Accessories Store – E-Commerce Inventory & Search System** is a C++ console-based application designed to manage products, organize inventory, search and filter items, process shopping cart transactions, and showcase official partner brands.

The system focuses on managing bags and accessories from four partner brands:

1. **Herschel**
2. **Anello**
3. **Guess**
4. **Jansport**

It uses different Data Structures and Algorithms (DSA) to demonstrate how inventory management and shopping cart operations can be performed efficiently.

---

## Project Objectives

The main objectives of this project are:

- To organize and display the complete product catalog.
- To filter products according to their official brands.
- To search products using keywords.
- To filter products based on price ranges.
- To manage shopping cart items.
- To process customer checkout transactions.
- To restore previous actions using an undo feature.
- To display partner brand banners.
- To sort inventory according to price, stock, and brand.
- To demonstrate the practical application of Data Structures and Algorithms in C++.

---

## Official Partner Brands

The system includes four official partner brands:

| Brand | Description |
|---|---|
| Herschel | Classic designs for travel and everyday use |
| Anello | Stylish everyday bags and accessories |
| Guess | Fashion bags and accessories |
| Jansport | Backpacks and everyday carry products |

**Important:** Only these four brands are accepted when adding a new product.

---

## Main Menu Features

The system provides the following ten main menu options:

| No. | Feature | Description |
|---|---|---|
| 1 | View Complete Catalog | Displays all available products, including their ID, name, category, brand, price, and stock quantity. |
| 2 | Filter Products by Official Brand | Displays products belonging to Herschel, Anello, Guess, or Jansport. |
| 3 | Search Products by Keyword | Searches products using their name, category, or brand. |
| 4 | Filter Products by Price Range | Displays products within the selected minimum and maximum price. |
| 5 | Add Item to Shopping Cart | Adds a selected product and quantity to the shopping cart. |
| 6 | Process Customer Checkout | Processes cart items using a first-in, first-out queue and updates product stock. |
| 7 | Perform Admin Undo Action | Reverses the most recent supported action using a stack. |
| 8 | Display Partner Brand Banner Showcase | Displays the four official partner brands using a circular linked list. |
| 9 | Sort Inventory Display | Sorts products by price, stock quantity, or brand. |
| 10 | Exit | Closes the application and displays the thank-you message. |

---

## Product Catalog

The system starts with eight sample products.

| Product ID | Product Name | Category | Brand | Price (PHP) | Stock |
|---|---|---|---|---:|---:|
| 1001 | Classic Backpack | Backpack | Herschel | 1,899.00 | 12 |
| 1002 | Mini Backpack | Backpack | Anello | 1,499.00 | 10 |
| 1003 | School Backpack | Backpack | Jansport | 1,299.00 | 15 |
| 1004 | Logo Shoulder Bag | Shoulder Bag | Guess | 2,299.00 | 7 |
| 1005 | Travel Tote Bag | Tote Bag | Herschel | 999.00 | 9 |
| 1006 | Crossbody Bag | Crossbody | Guess | 1,799.00 | 6 |
| 1007 | Canvas Tote | Tote Bag | Anello | 799.00 | 14 |
| 1008 | Laptop Backpack | Backpack | Jansport | 1,599.00 | 8 |

All prices are displayed in Philippine Peso (PHP).

---

## Data Structures and Algorithms Used

The project demonstrates the following Data Structures and Algorithms:

### 1. Vector

**Purpose:** Stores and manages the product inventory.

The vector holds product information, including:
- Product ID
- Product name
- Category
- Brand
- Price
- Stock quantity

### 2. Doubly Linked List

**Purpose:** Manages shopping cart items.

Each cart node contains:
- Product information
- Previous node pointer
- Next node pointer

It allows the system to add items and traverse the shopping cart.

### 3. Queue

**Purpose:** Processes customer checkout transactions.

The queue follows the **FIFO (First In, First Out)** principle. The first item added to the checkout queue is processed first.

### 4. Stack

**Purpose:** Supports the Admin Undo Action feature.

The stack follows the **LIFO (Last In, First Out)** principle. The most recent supported action is reversed first.

### 5. Circular Linked List

**Purpose:** Displays the official partner brand showcase.

The circular linked list connects the four partner brands in a cycle.

### 6. Binary Search Tree (BST)

**Purpose:** Maintains a product tree organized using product IDs.

The tree is rebuilt when inventory changes. Its nodes contain product information and left and right child pointers.

### 7. Linear Search

**Purpose:** Searches products using keywords.

The system checks the product name, category, and brand to find matching results.

### 8. Binary Search

**Purpose:** Helps filter products within a selected price range.

The system sorts a copy of the inventory by price and uses `lower_bound()` and `upper_bound()` to identify matching products.

### 9. Insertion Sort

**Purpose:** Sorts products based on:
- Price (Low to High)
- Stock Quantity (High to Low)

### 10. Quick Sort

**Purpose:** Sorts products alphabetically by brand (A–Z).

---

## Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Main programming language |
| iostream | Input and output operations |
| iomanip | Formatting product tables and prices |
| string | Managing text information |
| vector | Product inventory storage |
| queue | Checkout processing |
| stack | Undo action management |
| algorithm | Sorting and searching operations |
| limits | Input validation |
| sstream | Price formatting |
| cctype | Case-insensitive keyword and brand comparison |
| windows.h | Windows console support |

---

## System Requirements

To compile and run the application, you need:

- A Windows, Linux, or macOS computer.
- A C++ compiler that supports C++11 or later.
- A code editor or IDE, such as:
  - Visual Studio Code
  - Code::Blocks
  - Dev-C++
  - Visual Studio
- A terminal or command prompt.

---

## How to Install and Run

### Step 1: Clone the Repository

Open your terminal and enter:

```bash
git clone https://github.com/cristinemaygesite-pixel/Gesite-Final-Output.git
```

### Step 2: Open the Project Folder

```bash
cd Gesite-Final-Output
```

### Step 3: Compile the C++ Program

Using GCC:

```bash
g++ -std=c++11 main.cpp -o main
```

### Step 4: Run the Program

For Windows:

```bash
main.exe
```

For Linux or macOS:

```bash
./main
```

---

## Sample Main Menu

```text
===========================================================
                 BAGS & ACCESSORIES
                  E-COMMERCE INVENTORY
                     & SEARCH SYSTEM
===========================================================

1. View Complete Catalog
2. Filter Products by Official Brand
3. Search Products by Keyword
4. Filter Products by Price Range
5. Add Item to Shopping Cart
6. Process Customer Checkout
7. Perform Admin Undo Action
8. Display Partner Brand Banner Showcase
9. Sort Inventory Display
10. Exit

===========================================================

Enter your choice:
```

---

## Sample Product Display

```text
ID     Product                  Category         Brand
---------------------------------------------------------------
1001   Classic Backpack         Backpack         Herschel
1002   Mini Backpack            Backpack         Anello
1003   School Backpack          Backpack         Jansport
1004   Logo Shoulder Bag        Shoulder Bag     Guess
1005   Travel Tote Bag          Tote Bag         Herschel
1006   Crossbody Bag            Crossbody        Guess
1007   Canvas Tote              Tote Bag         Anello
1008   Laptop Backpack          Backpack         Jansport
---------------------------------------------------------------
```

---

## Important System Notes

- The application starts with eight sample products.
- Product prices are displayed in PHP.
- Product IDs must be unique when adding a product.
- Only Herschel, Anello, Guess, and Jansport are accepted as partner brands.
- The shopping cart checks available stock before accepting a requested quantity.
- Checkout decreases the available stock.
- The undo feature supports reversing checkout transactions and removing products added through the `addNewProduct()` function.
- Product and transaction information is stored in program memory. It is not permanently saved to a database or external file.
- Restarting the application restores the original sample inventory.

**Implementation note:** The `addNewProduct()` function is present in the source code, but it is not currently connected to the ten-option main menu. The Binary Search Tree is also maintained in the code, but there is no menu option that performs a BST search or displays its traversal.

---

## Project Purpose

This project demonstrates the use of C++ programming, Data Structures, and Algorithms in a practical e-commerce inventory management scenario.

It combines product organization, brand filtering, keyword searching, price filtering, shopping cart management, checkout processing, undo operations, and inventory sorting in one console-based application.

---

## Repository Information

**Project Name:** Bags & Accessories Store – E-Commerce Inventory & Search System

**Programming Language:** C++

**Project Type:** Data Structures and Algorithms Final Project

**Official Partner Brands:** Herschel, Anello, Guess, and Jansport

**Repository:** [Gesite-Final-Output on GitHub](https://github.com/cristinemaygesite-pixel/Gesite-Final-Output)

**Website:** [Visit the Project Website](https://cristinemaygesite-pixel.github.io/Gesite-Final-Output/)

---

## Authors

Developed as an academic project for the Data Structures and Algorithms course.

---

**Thank you for visiting the Bags & Accessories Store – E-Commerce Inventory & Search System!**
