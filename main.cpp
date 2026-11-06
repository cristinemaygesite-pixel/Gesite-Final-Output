#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <sstream>
#include <cctype>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
namespace Color
{
    const string RESET = "\033[0m";
    const string BOLD = "\033[1m";
    const string CYAN = "\033[1;36m";
    const string YELLOW = "\033[1;33m";
    const string GREEN = "\033[1;37m";
    const string RED = "\033[1;31m";
    const string BLUE = "\033[1;36m";
    const string WHITE = "\033[1;37m";
}
const int CONSOLE_WIDTH = 80;
void printCenteredBox(const vector<string> &lines, int width = 64)
{
    string margin(max(0, (CONSOLE_WIDTH - width) / 2), ' ');
    cout << margin << Color::CYAN << "+" << string(width - 2, '-') << "+" << Color::RESET << '\n';
    for (string line : lines)
    {
        if ((int)line.size() > width - 4)
            line = line.substr(0, width - 4);
        int left = (width - 2 - (int)line.size()) / 2;
        int right = width - 2 - (int)line.size() - left;
        string textColor = Color::WHITE;
        if (line.find("BAGS & ACCESSORIES") != string::npos)
            textColor = Color::CYAN;
        cout << margin << Color::CYAN << "|" << Color::RESET << string(left, ' ') << textColor << Color::BOLD << line << Color::RESET << string(right, ' ') << Color::CYAN << "|" << Color::RESET << '\n';
    }
    cout << margin << Color::CYAN << "+" << string(width - 2, '-') << "+" << Color::RESET << '\n';
}
string formatPrice(double price)
{
    stringstream ss;
    ss << fixed << setprecision(2) << price;
    string value = ss.str();
    size_t decimal = value.find('.');
    if (decimal != string::npos)
        for (int i = (int)decimal - 3; i > 0; i -= 3)
            value.insert(i, ",");
    return "PHP " + value;
}
string lowerText(string value)
{
    transform(value.begin(), value.end(), value.begin(), [](unsigned char c)
              { return (char)tolower(c); });
    return value;
}
struct Product
{
    int id;
    string name, category, brand;
    double price;
    int stockQuantity;
};
struct CartItem
{
    int productId;
    string productName;
    double price;
    int quantity;
};
struct UndoAction
{
    string type;
    Product product;
    int quantity;
};
struct CartNode
{
    CartItem item;
    CartNode *prev, *next;
    CartNode(const CartItem &value) : item(value), prev(nullptr), next(nullptr) {}
};
class ShoppingCart
{
private:
    CartNode *head, *tail;

public:
    ShoppingCart() : head(nullptr), tail(nullptr) {}
    ~ShoppingCart()
    {
        clear();
    }
    bool empty() const
    {
        return head == nullptr;
    }
    void addItem(const CartItem &item)
    {
        CartNode *node = new CartNode(item);
        if (!head)
            head = tail = node;
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    int quantityOf(int id) const
    {
        int total = 0;
        for (CartNode *p = head;
             p; p = p->next)
            if (p->item.productId == id)
                total += p->item.quantity;
        return total;
    }
    void displayCart() const
    {
        if (empty())
        {
            cout << Color::YELLOW << "\nShopping cart is empty.\n"
                 << Color::RESET;
            return;
        }
        double total = 0;
        cout << "\n========== SHOPPING CART ==========\n";
        for (CartNode *p = head;
             p; p = p->next)
        {
            double subtotal = p->item.price * p->item.quantity;
            total += subtotal;
            cout << "Product: " << p->item.productName << "\nQuantity: " << p->item.quantity << "\nSubtotal: " << formatPrice(subtotal) << "\n----------------------------------\n";
        }
        cout << "CART TOTAL: " << formatPrice(total) << '\n';
    }
    void moveToQueue(queue<CartItem> &q)
    {
        while (head)
        {
            q.push(head->item);
            CartNode *old = head;
            head = head->next;
            delete old;
        }
        tail = nullptr;
    }
    void clear()
    {
        while (head)
        {
            CartNode *old = head;
            head = head->next;
            delete old;
        }
        tail = nullptr;
    }
};
struct BrandNode
{
    string brand, banner;
    BrandNode *next;
    BrandNode(const string &b, const string &text) : brand(b), banner(text), next(nullptr) {}
};
class BrandShowcase
{
private:
    BrandNode *tail;

public:
    BrandShowcase() : tail(nullptr)
    {
        addBrand("Herschel", "CLASSIC DESIGN - Travel and everyday bags");
        addBrand("Anello", "SMART STYLE - Everyday bags and accessories");
        addBrand("Jansport", "ALWAYS WITH YOU - Backpacks and daily carry");
        addBrand("Guess", "ICONIC STYLE - Fashion bags and accessories");
    }
    ~BrandShowcase()
    {
        clear();
    }
    void addBrand(const string &brand, const string &banner)
    {
        BrandNode *node = new BrandNode(brand, banner);
        if (!tail)
        {
            tail = node;
            tail->next = tail;
        }
        else
        {
            node->next = tail->next;
            tail->next = node;
            tail = node;
        }
    }
    void displayCycle() const
    {
        if (!tail)
        {
            cout << "No partner brands available.\n";
            return;
        }
        cout << "\n======= PARTNER BRAND SHOWCASE =======\n";
        BrandNode *p = tail->next;
        do
        {
            cout << Color::GREEN << "\nBRAND: " << p->brand << "\nBANNER: " << p->banner << Color::RESET << '\n';
            p = p->next;
        } while (p != tail->next);
        cout << "\nCircular list cycle completed.\n";
    }
    void clear()
    {
        if (!tail)
            return;
        BrandNode *p = tail->next;
        tail->next = nullptr;
        while (p)
        {
            BrandNode *old = p;
            p = p->next;
            delete old;
        }
        tail = nullptr;
    }
};
struct BSTNode
{
    Product product;
    BSTNode *left, *right;
    BSTNode(const Product &p) : product(p), left(nullptr), right(nullptr) {}
};
class BagsAccessoriesStore
{
private:
    vector<Product> products;
    ShoppingCart cart;
    BrandShowcase brandShowcase;
    stack<UndoAction> undoStack;
    queue<CartItem> checkoutQueue;
    BSTNode *productTree = nullptr;
    int nextId = 1001;
    const vector<string> partnerBrands = {"Herschel", "Anello", "Jansport", "Guess"};
    void clearInputLine()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int readInt(const string &prompt, int minimum = 0)
    {
        int value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= minimum)
            {
                clearInputLine();
                return value;
            }
            cout << Color::RED << "Invalid input. Enter a whole number >= " << minimum << ".\n"
                 << Color::RESET;
            cin.clear();
            clearInputLine();
        }
    }
    double readPrice(const string &prompt)
    {
        double value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= 0 && value <= 1000000000.0)
            {
                clearInputLine();
                return value;
            }
            cout << Color::RED << "Invalid price. Please try again.\n"
                 << Color::RESET;
            cin.clear();
            clearInputLine();
        }
    }
    string readText(const string &prompt)
    {
        string value;
        while (true)
        {
            cout << prompt;
            getline(cin, value);
            if (value.find_first_not_of(" \t") != string::npos)
                return value;
            cout << Color::RED << "Input cannot be empty.\n"
                 << Color::RESET;
        }
    }
    Product *findProduct(int id)
    {
        for (auto &p : products)
            if (p.id == id)
                return &p;
        return nullptr;
    }
    BSTNode *insertBST(BSTNode *root, const Product &p)
    {
        if (!root)
            return new BSTNode(p);
        if (p.id < root->product.id)
            root->left = insertBST(root->left, p);
        else if (p.id > root->product.id)
            root->right = insertBST(root->right, p);
        return root;
    }
    void deleteBST(BSTNode *root)
    {
        if (!root)
            return;
        deleteBST(root->left);
        deleteBST(root->right);
        delete root;
    }
    void rebuildBST()
    {
        deleteBST(productTree);
        productTree = nullptr;
        for (const auto &p : products)
            productTree = insertBST(productTree, p);
    }
    void displayBSTInOrder(BSTNode *root) const
    {
        if (!root)
            return;
        displayBSTInOrder(root->left);
        printProduct(root->product);
        displayBSTInOrder(root->right);
    }
    void printHeader() const
    {
        cout << Color::YELLOW << left << setw(7) << "ID" << setw(25) << "Product" << setw(17) << "Category" << setw(13) << "Brand" << right << setw(15) << "Price" << setw(8) << "Stock" << Color::RESET << '\n';
        cout << string(85, '-') << '\n';
    }
    void printProduct(const Product &p) const
    {
        cout << left << setw(7) << p.id << setw(25) << p.name.substr(0, 23) << setw(17) << p.category.substr(0, 15) << setw(13) << p.brand.substr(0, 11) << right << setw(15) << formatPrice(p.price) << setw(8) << p.stockQuantity << '\n';
    }
    void displayProducts(const vector<Product> &list) const
    {
        if (list.empty())
        {
            cout << Color::YELLOW << "\nNo products found.\n"
                 << Color::RESET;
            return;
        }
        printHeader();
        for (const auto &p : list)
            printProduct(p);
        cout << string(85, '-') << '\n';
    }
    void seedProducts()
    {
        products = {
            {nextId++, "Classic Backpack", "Backpack", "Herschel", 1899.00, 12}, {nextId++, "Mini Backpack", "Backpack", "Anello", 1499.00, 10}, {nextId++, "School Backpack", "Backpack", "Jansport", 1299.00, 15}, {nextId++, "Logo Shoulder Bag", "Shoulder Bag", "Guess", 2299.00, 7}, {nextId++, "Travel Tote Bag", "Tote Bag", "Herschel", 999.00, 9}, {nextId++, "Crossbody Bag", "Crossbody", "Guess", 1799.00, 6}, {nextId++, "Canvas Tote", "Tote Bag", "Anello", 799.00, 14}, {nextId++, "Laptop Backpack", "Backpack", "Jansport", 1599.00, 8}};
        rebuildBST();
    }
    void viewCatalog() const
    {
        printCenteredBox({"COMPLETE PRODUCT CATALOG", "All Products with Brand Affiliations"});
        displayProducts(products);
    }
    void filterByBrand()
    {
        while (true)
        {
            // PAGE 1: BRAND INPUT
            clearScreen();
            printCenteredBox({"FILTER PRODUCTS BY OFFICIAL BRAND"});
            cout << "\nAvailable Partner Brands:\n";
            for (const auto &brand : partnerBrands)
                cout << "- " << brand << '\n';
            cout << "\nEnter 0 to return to the main menu.\n";
            string brand = readText("\nEnter brand name: ");
            if (brand == "0")
            {
                cout << "\nReturning to main menu...\n";
                return;
            }
            string selectedBrand = lowerText(brand);
            bool validBrand = false;
            for (const auto &partner : partnerBrands)
            {
                if (selectedBrand == lowerText(partner))
                {
                    validBrand = true;
                    break;
                }
            }
            if (!validBrand)
            {
                cout << Color::RED << "\nInvalid brand name. Please try again." << Color::RESET << '\n';
                cout << "\nPress Enter to try again...";
                cin.get();
                continue;
            }
            vector<Product> results;
            for (const auto &p : products)
            {
                if (lowerText(p.brand) == selectedBrand)
                    results.push_back(p);
            }
            // PAGE 2: BRAND RESULTS
            clearScreen();
            printCenteredBox({"BRAND FILTER RESULTS"});
            cout << "\nSelected Brand: " << brand << "\n\n";
            displayProducts(results);
            cout << "\n==========================================\n";
            cout << "Press Enter to search another brand.\n";
            cout << "Enter 0 to return to the main menu.\n";
            string option;
            cout << "\nYour choice: ";
            getline(cin, option);
            if (option == "0")
            {
                return;
            }
        }
    }
    void searchByKeyword()
    {
        printCenteredBox({"SEARCH PRODUCTS BY KEYWORD", "Linear Search"});
        string keyword = lowerText(readText("\nEnter product, category, or brand keyword: "));
        vector<Product> results;
        for (const auto &p : products)
        {
            string combined = lowerText(p.name + " " + p.category + " " + p.brand);
            if (combined.find(keyword) != string::npos)
                results.push_back(p);
        }
        cout << "\nSEARCH RESULTS:\n";
        displayProducts(results);
    }
    void filterByPriceRange()
    {
        printCenteredBox({"FILTER PRODUCTS BY PRICE RANGE", "Binary Search"});
        double minimum = readPrice("\nMinimum price (PHP): ");
        double maximum = readPrice("Maximum price (PHP): ");
        if (minimum > maximum)
        {
            cout << Color::RED << "\nMinimum price cannot exceed maximum price.\n"
                 << Color::RESET;
            return;
        }
        vector<Product> sorted = products;
        sort(sorted.begin(), sorted.end(), [](const Product &a, const Product &b)
             { return a.price < b.price; });
        auto first = lower_bound(sorted.begin(), sorted.end(), minimum, [](const Product &p, double value)
                                 { return p.price < value; });
        auto last = upper_bound(sorted.begin(), sorted.end(), maximum, [](double value, const Product &p)
                                { return value < p.price; });
        vector<Product> results(first, last);
        cout << "\nPRICE RANGE: " << formatPrice(minimum) << " to " << formatPrice(maximum) << '\n';
        displayProducts(results);
    }
    void addToShoppingCart()
    {
        printCenteredBox({"ADD ITEM TO SHOPPING CART", "Doubly Linked List Navigation"});
        displayProducts(products);
        int id = readInt("\nEnter Product ID: ", 1);
        Product *p = findProduct(id);
        if (!p)
        {
            cout << Color::RED << "\nProduct not found.\n"
                 << Color::RESET;
            return;
        }
        cout << "\nSelected: " << p->name << "\nPrice: " << formatPrice(p->price) << "\nAvailable stock: " << p->stockQuantity << '\n';
        if (p->stockQuantity <= 0)
        {
            cout << Color::RED << "This product is out of stock.\n"
                 << Color::RESET;
            return;
        }
        int quantity = readInt("\nEnter quantity: ", 1);
        int alreadyInCart = cart.quantityOf(id);
        if (quantity > p->stockQuantity - alreadyInCart)
        {
            cout << Color::RED << "\nRequested quantity exceeds available stock.\n"
                 << Color::RESET;
            return;
        }
        cart.addItem({p->id, p->name, p->price, quantity});
        cout << Color::GREEN << "\nItem successfully added to shopping cart!\n"
             << Color::RESET;
        cart.displayCart();
    }
    void processCheckout()
    {
        printCenteredBox({"PROCESS CUSTOMER CHECKOUT QUEUE", "FIFO Order Processing"});
        if (cart.empty() && checkoutQueue.empty())
        {
            cout << Color::YELLOW << "\nNo items are waiting for checkout.\n"
                 << Color::RESET;
            return;
        }
        cart.moveToQueue(checkoutQueue);
        double grandTotal = 0;
        int processed = 0;
        while (!checkoutQueue.empty())
        {
            CartItem item = checkoutQueue.front();
            checkoutQueue.pop();
            Product *p = findProduct(item.productId);
            if (!p || p->stockQuantity < item.quantity)
            {
                cout << Color::RED << "\nOrder skipped: stock unavailable for " << item.productName << ".\n"
                     << Color::RESET;
                continue;
            }
            double subtotal = p->price * item.quantity;
            p->stockQuantity -= item.quantity;
            grandTotal += subtotal;
            processed++;
            UndoAction action = {"CHECKOUT", *p, item.quantity};
            undoStack.push(action);
            cout << Color::GREEN << "\nProduct: " << item.productName << "\nQuantity: " << item.quantity << "\nSubtotal: " << formatPrice(subtotal) << "\nRemaining stock: " << p->stockQuantity << "\n----------------------------------\n"
                 << Color::RESET;
        }
        rebuildBST();
        cout << Color::CYAN << "\n========== CHECKOUT SUMMARY ==========\n"
             << Color::RESET;
        cout << "Processed items: " << processed << "\nGrand total: " << formatPrice(grandTotal) << "\nCheckout complete!\n";
    }
    void undoAction()
    {
        printCenteredBox({"ADMIN UNDO ACTION", "LIFO Stack Pop"});
        if (undoStack.empty())
        {
            cout << Color::YELLOW << "\nNo action is available to undo.\n"
                 << Color::RESET;
            return;
        }
        UndoAction action = undoStack.top();
        undoStack.pop();
        if (action.type == "ADD_PRODUCT")
        {
            auto it = find_if(products.begin(), products.end(), [&](const Product &p)
                              { return p.id == action.product.id; });
            if (it != products.end())
            {
                cout << Color::GREEN << "\nUndoing added product: " << it->name << '\n'
                     << Color::RESET;
                products.erase(it);
                rebuildBST();
            }
        }
        else if (action.type == "CHECKOUT")
        {
            Product *p = findProduct(action.product.id);
            if (p)
            {
                p->stockQuantity += action.quantity;
                cout << Color::GREEN << "\nUndo successful!" << "\nRestored " << action.quantity << " unit(s) of " << p->name << "\nUpdated stock: " << p->stockQuantity << '\n'
                     << Color::RESET;
                rebuildBST();
            }
        }
    }
    void showBrandBanners() const
    {
        printCenteredBox({"PARTNER BRAND BANNER SHOWCASE", "Circular Linked List Cycle"});
        brandShowcase.displayCycle();
    }
    void insertionSortByPrice(vector<Product> &list)
    {
        for (size_t i = 1; i < list.size(); i++)
        {
            Product key = list[i];
            int j = (int)i - 1;
            while (j >= 0 && list[j].price > key.price)
            {
                list[j + 1] = list[j];
                j--;
            }
            list[j + 1] = key;
        }
    }
    void insertionSortByStock(vector<Product> &list)
    {
        for (size_t i = 1; i < list.size(); i++)
        {
            Product key = list[i];
            int j = (int)i - 1;
            while (j >= 0 && list[j].stockQuantity < key.stockQuantity)
            {
                list[j + 1] = list[j];
                j--;
            }
            list[j + 1] = key;
        }
    }
    int partitionByBrand(vector<Product> &list, int low, int high)
    {
        string pivot = lowerText(list[high].brand);
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (lowerText(list[j].brand) <= pivot)
            {
                i++;
                swap(list[i], list[j]);
            }
        }
        swap(list[i + 1], list[high]);
        return i + 1;
    }
    void quickSortByBrand(vector<Product> &list, int low, int high)
    {
        if (low < high)
        {
            int pivot = partitionByBrand(list, low, high);
            quickSortByBrand(list, low, pivot - 1);
            quickSortByBrand(list, pivot + 1, high);
        }
    }
    void sortInventory()
    {
        printCenteredBox({"SORT INVENTORY DISPLAY", "Insertion Sort and Quick Sort"});
        cout << "\n1. Sort by Price (Low to High)" << "\n2. Sort by Stock (High to Low)" << "\n3. Sort by Brand (A-Z)\n";
        int choice = readInt("\nChoose sorting option: ", 1);
        if (choice < 1 || choice > 3)
        {
            cout << Color::RED << "\nInvalid sorting option.\n"
                 << Color::RESET;
            return;
        }
        vector<Product> sorted = products;
        if (choice == 1)
            insertionSortByPrice(sorted);
        else if (choice == 2)
            insertionSortByStock(sorted);
        else if (!sorted.empty())
            quickSortByBrand(sorted, 0, (int)sorted.size() - 1);
        cout << "\nSORTED INVENTORY:\n";
        displayProducts(sorted);
    }
    void addNewProduct()
    {
        printCenteredBox({"ADD NEW PRODUCT TO INVENTORY"});
        Product p;
        p.id = readInt("Enter product ID: ", 1);
        if (findProduct(p.id))
        {
            cout << Color::RED << "Product ID already exists.\n"
                 << Color::RESET;
            return;
        }
        p.name = readText("Enter product name: ");
        p.category = readText("Enter category: ");
        p.brand = readText("Enter brand (Herschel/Anello/Jansport/Guess): ");
        string brand = lowerText(p.brand);
        if (brand == "herschel")
            p.brand = "Herschel";
        else if (brand == "anello")
            p.brand = "Anello";
        else if (brand == "jansport")
            p.brand = "Jansport";
        else if (brand == "guess")
            p.brand = "Guess";
        else
        {
            cout << Color::RED << "Invalid partner brand.\n"
                 << Color::RESET;
            return;
        }
        p.price = readPrice("Enter price (PHP): ");
        p.stockQuantity = readInt("Enter stock quantity: ");
        products.push_back(p);
        rebuildBST();
        undoStack.push({"ADD_PRODUCT", p, 0});
        if (p.id >= nextId)
            nextId = p.id + 1;
        cout << Color::GREEN << "Product successfully added!\n"
             << Color::RESET;
    }
    void showMainMenu() const
    {
        printCenteredBox({"BAGS & ACCESSORIES STORE", "E-COMMERCE INVENTORY", "& SEARCH SYSTEM"}, 55);
        vector<string> lines = {"1. View Complete Catalog", "2. Filter Products by Official Brand", "3. Search Products by Keyword", "4. Filter Products by Price Range", "5. Add Item to Shopping Cart", "6. Process Customer Checkout", "7. Perform Admin Undo Action", "8. Display Partner Brand Banner Showcase", "9. Sort Inventory Display", "10. Exit"};
        int width = 75;
        string margin(max(0, (CONSOLE_WIDTH - width) / 2), ' ');
        cout << margin << Color::CYAN << "+" << string(width - 2, '-') << "+" << Color::RESET << '\n';
        for (size_t i = 0; i < lines.size(); i++)
        {
            string line = lines[i];
            int left = 2;
            int right = width - 2 - left - (int)line.size();
            cout << margin << Color::CYAN << "|" << Color::RESET << string(max(0, left), ' ');
            if (line.find("---") != string::npos)
            {
                cout << Color::CYAN << Color::BOLD << line << Color::RESET;
            }
            else if (line.find("10. Exit") != string::npos)
            {
                cout << Color::CYAN << Color::BOLD << "10." << Color::RESET << Color::WHITE << " Exit" << Color::RESET;
            }
            else if (isdigit(line[0]))
            {
                size_t dot = line.find('.');
                cout << Color::CYAN << Color::BOLD << line.substr(0, dot + 1) << Color::RESET << Color::WHITE << line.substr(dot + 1) << Color::RESET;
            }
            else
            {
                cout << Color::WHITE << Color::BOLD << line << Color::RESET;
            }
            cout << string(max(0, right), ' ') << Color::CYAN << "|" << Color::RESET << '\n';
        }
        cout << margin << Color::CYAN << "+" << string(width - 2, '-') << "+" << Color::RESET << "\n\n";
    }

public:
    BagsAccessoriesStore()
    {
        seedProducts();
    }
    ~BagsAccessoriesStore()
    {
        deleteBST(productTree);
    }
    void clearScreen() const
    {
#ifdef _WIN32
        system("cls");
#else
        cout << "\033[2J\033[H" << flush;
#endif
    }
    void pauseBeforeMenu() const
    {
        cout << "\n"
             << Color::CYAN << "Press Enter to return to the main menu..." << Color::RESET;
        cin.get();
        clearScreen();
    }
    void run()
    {
        while (true)
        {
            clearScreen();
            showMainMenu();
            int choice = readInt(Color::CYAN + Color::BOLD + "Enter your choice: " + Color::RESET, 1);
            clearScreen();
            switch (choice)
            {
            case 1:
                viewCatalog();
                break;
            case 2:
                filterByBrand();
                break;
            case 3:
                searchByKeyword();
                break;
            case 4:
                filterByPriceRange();
                break;
            case 5:
                addToShoppingCart();
                break;
            case 6:
                processCheckout();
                break;
            case 7:
                undoAction();
                break;
            case 8:
                showBrandBanners();
                break;
            case 9:
                sortInventory();
                break;
            case 10:
                printCenteredBox({"THANK YOU!", "BAGS & ACCESSORIES STORE", "Thank you for using our system."});
                return;
            default:
                cout << Color::RED << "\nInvalid choice. Select 1 to 10.\n"
                     << Color::RESET;
            }
            pauseBeforeMenu();
        }
    }
};
int main()
{
#ifdef _WIN32 SetConsoleOutputCP(CP_UTF8); SetConsoleCP(CP_UTF8);
#endif BagsAccessoriesStore store; store.run();
    return 0;
}
