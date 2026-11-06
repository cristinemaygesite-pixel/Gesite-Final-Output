BAGS & ACCESSORIES STORE
E-Commerce Inventory & Search System
Project Description
The Bags & Accessories Store -- E-Commerce Inventory & Search System
is a console-based C++ application for displaying and managing a sample
inventory of bags and accessories from selected partner brands. It
allows users to browse products, filter products by brand or price
range, search by keyword, add products to a shopping cart, process
checkout, undo supported actions, view partner-brand banners, and sort
the inventory.

The program uses several data structures and algorithms to demonstrate
concepts from Data Structures and Algorithms (DSA). Product prices are
displayed in PHP.
1. Main Menu Features
The program displays the following ten menu options:
                       No. Feature               Description

                         1 View Complete Catalog Displays all products
                                                 with their ID,
                                                 product name,
                                                 category, brand,
                                                 price, and available
                                                 stock.

                         2 Filter Products by    Displays products
                           Official Brand        belonging to a
                                                 selected partner
                                                 brand.

                         3 Search Products by    Searches product
                           Keyword               names, categories,
                                                 and brand names using
                                                 a keyword.

                         4 Filter Products by    Displays products
                           Price Range           whose prices fall
                                                 within the minimum
                                                 and maximum PHP
                                                 amounts entered by
                                                 the user.

                         5 Add Item to Shopping  Adds a selected
                           Cart                  product and quantity
                                                 to the shopping cart,
                                                 subject to available
                                                 stock.

                         6 Process Customer      Processes cart items
                           Checkout              in queue order,
                                                 calculates subtotals
                                                 and the grand total,
                                                 and updates inventory
                                                 stock.

                         7 Perform Admin Undo    Reverses a supported
                           Action                checkout or
                                                 product-add action
                                                 stored in the undo
                                                 stack.

                         8 Display Partner Brand Displays the partner
                           Banner Showcase       brands and their
                                                 banner descriptions
                                                 using a circular
                                                 linked list.

                         9 Sort Inventory        Sorts products by
                           Display               price, stock
                                                 quantity, or brand.

                        10 Exit                  Displays the
                                                 thank-you message and
                                                 closes the program.

Note: The source code contains an addNewProduct() function, but
that function is not connected to any option in the displayed main menu.
Therefore, adding a new product is not listed as an available menu
feature.
2. Partner Brands
The program uses four partner brands:
1. Herschel -- Classic design; travel and everyday bags.
2. Anello -- Smart style; everyday bags and accessories.
3. Jansport -- Backpacks and daily-carry products.
4. Guess -- Fashion bags and accessories.
Brand filtering accepts these partner-brand names without requiring the
user to match uppercase and lowercase letters.
3. Sample Product Inventory
The program starts with eight sample products:
Product ID Product Name        Category       Brand        Price (PHP)   Stock

      1001 Classic Backpack    Backpack       Herschel        1,899.00      12
      1002 Mini Backpack       Backpack       Anello          1,499.00      10
      1003 School Backpack     Backpack       Jansport        1,299.00      15
      1004 Logo Shoulder Bag   Shoulder Bag   Guess           2,299.00       7
      1005 Travel Tote Bag     Tote Bag       Herschel          999.00       9
      1006 Crossbody Bag       Crossbody      Guess           1,799.00       6
      1007 Canvas Tote         Tote Bag       Anello            799.00      14
      1008 Laptop Backpack     Backpack       Jansport        1,599.00       8
These are sample records initialized by the program. They are not loaded
from an external database or file.
4. Data Structures Used
  Data Structure          Where It Is Used        Purpose
  Vector                  Product inventory       Stores the product
records and supports
iteration, filtering,
and sorting.

  Doubly Linked List      Shopping cart           Stores cart items in
nodes connected through
previous and next
pointers.

  Queue (FIFO)            Checkout processing     Processes cart items in
first-in, first-out
order.

  Stack (LIFO)            Undo actions            Stores supported
actions so the most
recent action can be
undone first.

  Circular Linked List    Partner brand showcase  Connects the brand
nodes in a cycle,
allowing the showcase
to traverse the brands
and return to the first
node.
Binary Search Tree      Product records indexed Inserts products
(BST)                   by product ID           according to their IDs
and is rebuilt when
inventory changes.
Brief Explanation
- Vector: Keeps the product catalog in a collection that can be
  traversed and copied for sorting.
- Doubly Linked List: Each cart node points to both the previous
  and next node. The cart can display items and transfer them to the
  checkout queue.
- Queue: Uses FIFO order. The item added first to the queue is
  processed first.
- Stack: Uses LIFO order. The latest supported action is removed
  first when the undo option is selected.
- Circular Linked List: The last brand node points back to the
  first brand node.
- Binary Search Tree: Places lower product IDs on the left and
  higher product IDs on the right. The tree is rebuilt from the
  product vector after relevant inventory updates. The source also
  includes an in-order display helper, although the main menu does not
  call that helper.
5. Algorithms Used
  Algorithm               Code Use                Purpose
  Linear Search           Keyword search          Checks each product's
name, category, and
brand for the entered
keyword.

  Binary Search Range     Price-range filtering   Uses lower_bound()
Functions                                       and upper_bound() on
a price-sorted product
list to find the
selected range.

  Insertion Sort          Price sorting           Arranges products from
lowest to highest
price.

  Insertion Sort          Stock sorting           Arranges products from
highest to lowest stock
quantity.

  Quick Sort              Brand sorting           Arranges products
alphabetically by brand
name.

  BST Insertion           Product tree            Inserts product records
based on product ID.
In-order Traversal      BST helper function     Visits the left
subtree, current
product, and right
subtree; the helper is
present in the code but
is not called by the
main menu.
6. Shopping Cart and Checkout Process
1. The user selects Add Item to Shopping Cart.
2. The program displays the product catalog.
3. The user enters a product ID and quantity.
4. The program checks whether the product exists and whether the
   requested quantity is within the available stock after considering
   items already in the cart.
5. The selected item is stored in the doubly linked list.
6. When the user selects Process Customer Checkout, cart items are
   transferred to the checkout queue.
7. The queue processes items in FIFO order.
8. The program calculates each item's subtotal and the grand total.
9. The purchased quantities are deducted from the product inventory.
10. The program stores checkout actions in the undo stack so a checkout
    action can be reversed using the undo option.
The displayed price format is PHP 1,234.00, with two decimal places
and comma separators for thousands.
7. Undo Function
The undo feature uses a stack. The source code stores two action types:
- CHECKOUT: Restores the quantity deducted from the product's
  stock during checkout.
- ADD_PRODUCT: Removes a product that was added through the
  addNewProduct() function.
The undo function handles these action types in last-in, first-out
order. However, the addNewProduct() function is not available through
the current main menu.
8. Input Validation
The program includes input checks for the following:
- Whole-number inputs must meet the minimum value requested by the
  program.
- Prices must be non-negative and cannot exceed the limit set in the
  code.
- Text fields cannot be left blank.
- The minimum price cannot be greater than the maximum price.
- The selected product ID must exist before an item can be added to
  the cart.
- The requested cart quantity must not exceed the remaining available
  stock.
- The brand filter checks whether the entered brand is one of the
  listed partner brands.
- Invalid menu and sorting choices display an error message.
9. Console Display
The application uses console formatting to make its output easier to
read:
- Centered title and menu boxes.
- Colored headings and messages using ANSI escape codes.
- Product information displayed in columns.
- PHP currency formatting.
- A screen-clearing function for Windows and non-Windows systems.
On Windows, the program includes the Windows console header and sets the
console input/output code page to UTF-8.
10. Requirements
- A C++ compiler that supports C++11 or later.
- Visual Studio Code, Code::Blocks, Dev-C++, or another C++
  IDE/editor.
- A terminal or console for running the program.
The source code uses standard C++ headers, plus windows.h when
compiled on Windows.
11. How to Compile and Run
Using Visual Studio Code on Windows
1. Create a project folder named BagsAccessoriesStore.
2. Save the complete C++ source code inside the folder as main.cpp.
3. Open the folder in Visual Studio Code.
4. Open the integrated terminal.
5. Compile the program using:
g++ -std=c++17 main.cpp -o BagsAccessoriesStore
6. Run the program using:
.\BagsAccessoriesStore.exe
If the g++ command is not recognized, install and configure a C++
compiler such as MinGW-w64 before compiling.
Using a Different C++ IDE
Create a C++ console project, add the source code as the main source
file, build the project, and run it in the IDE's console.
12. Project Folder Structure
BagsAccessoriesStore/
│
├── main.cpp
│
└── README.md
- main.cpp -- Contains the complete C++ source code, data
  structures, algorithms, menu, and program execution.
- README.md -- Contains the project description, features, data
  structures, algorithms, requirements, and instructions for compiling
  and running the program.
13. Limitations
- The program uses sample inventory records stored in the source code.
- Product data is not saved to a database or external file. Changes
  made while the program is running are not persistent after the
  program closes.
- The current main menu does not provide an option to add a new
  product, even though an addNewProduct() function exists in the
  source.
- The program is a console-based project and does not include a
  graphical user interface or online payment integration.
- The BST in-order display helper is implemented but is not used by
  the current menu flow.
14. Conclusion
The Bags & Accessories Store -- E-Commerce Inventory & Search System
demonstrates how data structures and algorithms can be applied to a
simple inventory and shopping workflow. It combines a vector, doubly
linked list, queue, stack, circular linked list, and binary search tree
with searching and sorting algorithms. The program provides catalog
browsing, product filtering, keyword searching, cart management,
checkout processing, undo support, brand showcase, and inventory sorting
in a centered and color-formatted console interface.
