
/* Tugas Besar Pemrograman Berorientasi Objek Kelompok 1 (Program untuk pemesanan treatment nail art)

 Ketua : Yohana Septamia (221402056)

 Anggota :

    - Andre Prayuda Sitompul (211402076)

    - Devandra Deal Fatahilla (221402040)

    - Sabrina Marisi Siahaan (221402078)

    - Muhammad Irvi Hafizi Manullang (221402118)
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <ctime>
#include<iomanip>
#include <cstdlib>

using namespace std;

//mendefinisikan kelas untuk data nama client
class client {
protected:
    string Nama;
public:
    //implementasi encapsulation
    string getNama() const{
        return Nama;
    }

    //constructor
    client(string nama) {
        Nama = nama;
    }

    //destructor
    ~client() {
        cout << "\n " << Nama << ", your booking is already done. Enjoy your treatment. Thank you." << endl;
    }
};

//struct untuk kategori dari nail art
struct Category {
    string name;
    string description;
    string time;
    double price;

    //constructor
    Category(string n, string desc, string t, double p) {
        name = n;
        description = desc;
        time = t;
        price = p;
    }

    //fungsi untuk menginisialisasi detail yang akan ditampilkan dari kategori yang dipilih client
    void displayDetails() {
        cout << "\n\tCategory: " << name << endl;
        cout << "\n\tPrice: Rp " << price << endl;
        cout << "\n\tDescription: " << description << endl;
        cout << "\n\tTime: " << time << endl;
    }
};

//fungsi untuk menampilkan pilihan kategori untuk nantinya dipilih oleh client
//kategori yg pertama kali dipilih oleh client
void displayCategories(const vector<Category>& categories) {
    for (int i = 0; i < categories.size(); i++) {
        cout << "\t" << (i + 1) << ". " << categories[i].name << endl;
    }
}

//menampilkan pilihan kategori yang available untuk client
void lanjut(const vector<Category>& categories) {
    cout << "\n\tAvailable Categories:" << endl;
    displayCategories(categories);
}

//menampilkan detail dari kategori yang dipilih client
void displayCategoryDetails(const vector<Category>& categories, int categoryIndex) {
    if (categoryIndex >= 1 && categoryIndex <= categories.size()) {
        Category selectedCategory = categories[categoryIndex - 1];
        selectedCategory.displayDetails();
    } else {
        cout << "\n\tInvalid category selection." << endl;
        exit(0);
    }
}

double invoice(const client& customer, const string& addOnList, const string& dayList, double hargaAddOn, double price) {
    //mendapatkan waktu pemesanan client
    time_t tmNow = time(0);
    char *dt = ctime(&tmNow);

    double subtotal = price + hargaAddOn;
    double tax = 0.05 * subtotal;

    double total = subtotal + tax;

    //menuliskan invoice pada file txt
    ofstream invoiceFile;
    invoiceFile.open("invoice.txt", ios::out | ios::trunc);
    if (invoiceFile.is_open()) {
        invoiceFile << "\n\t------------ INVOICE --------------" << endl;
        invoiceFile << "\n\tCustomer Name: " << customer.getNama() << endl;
        invoiceFile << "\n\tAdd On: " << addOnList << ", Price: " << fixed << setprecision(0) << hargaAddOn << endl;
        invoiceFile << "\n\tDay: " << dayList << endl;
        invoiceFile << "\n\tBooked at: " << dt << endl;

        invoiceFile << "\n\tSubtotal : " << fixed << setprecision(0) <<subtotal << endl;
        invoiceFile << "\n\tTax(5%) : " << fixed << setprecision(0) << tax << endl;

        invoiceFile << "\n\tTotal : " << fixed << setprecision(0) <<total << endl;
    }

    invoiceFile.close();

    return total;
}

void printInvoice()
{
    //membaca file txt dan memprintnya ke console
    ifstream invoiceFile;
    invoiceFile.open("invoice.txt", ios::in);
    {
        string line;
        if(invoiceFile.is_open()){
            while(getline(invoiceFile, line))
            {
                cout << line << endl;
            }
        }
        invoiceFile.close();
    }
}

//fungsi untuk melakukan pembayaran oleh client
void payment(double total) {
    double pay;
    cout << "\n\tInput your payment: ";
    cin >> pay;
    while (pay < total) {
        cout << "\n\tPayment failed, please try again: ";
        cin >> pay;
    }
    if(pay != total){
    double change = pay - total;
    cout << "\n\tPayment Success. Here is your change: " << change << endl;
    } else if (pay = total){
    cout << "\n\tPayment Success." << endl;
    }

}


int main() {
    system("color E0");
    string clientName;
    cout << "\n\tWhat can we call you? ";
    cin >> clientName;

    client customer(clientName);
    system("cls");

    cout << "\n\tHello " << customer.getNama() << " welcome to our nail art salon\n" << endl;

    cout << "\n\tThese are our menus: " << endl;
    cout << "\n\t1. Enhancements - Acrylics" << endl;
    cout << "\n\t2. Enhancements - SNS or Ombre" << endl;
    cout << "\n\t3. Enhancements - UV Gel" << endl;
    cout << "\n\t4. Enhancements - Gel powder" << endl;
    cout << "\n\t5. billills and Repairs" << endl;
    cout << "\n\t6. Manicures" << endl;
    cout << "\n\t7. Pedicures" << endl;
    cout << "\n\t8. Take off only" << endl;

    int pilihMenu;
    cout << "\n\tChoose the menu you want to book: ";
    cin >> pilihMenu;
    system("cls");
    if(pilihMenu > 8){
        cout << "\n\tInvalid menu selection" << endl;
        exit(0);
    }

    vector<Category> categories;

    if (pilihMenu == 1){
    categories = {
        Category("Acrylic Fullset with tips",
                 "Cuticle work, Extensions, file, buff and polish. This is for the connoisseur of enhancements.",
                 "1 hour 15 minutes",
                 672000),
        Category("Acrylic Overlay with Shellac",
                 "Cuticle work, Extensions, file, buff and Gel polish. In addition to your beautiful and durable set of nails.",
                 "1 hour 25 minutes",
                 821000),
        Category("Ombre Fullset - Short Length",
                 "Tired of your nails breaking all the time but long nails are not for you?",
                 "1 hour 10 minutes",
                 672000)
    };
    }

    else if (pilihMenu == 2){
    categories = {
        Category("Ombre Fullset - Short Length",
                 "The latest trend for french manicure. Long lasting. and non-chipping!",
                 "1 hour",
                 544000),
        Category("SNS Manicure",
                 "We're proud to be one very very few places to do this! It's the only nail product that has\n\ta Vitamin E and Calcium built into the product. The Calcium penetrates the nail bed\n\tand the Vitamin E strengthens your natural nails whilst leaving a long lasting effect",
                 "1 hour",
                 821000),
        Category("SNS Fullset with Tips (short length)",
                 "We're proud to be one very very few places to do this! It's the only nail product that has\n\ta Vitamin E and Calcium built into the product. The Calcium penetrates the nail bed\n\tand the Vitamin E strengthens your natural nails whilst leaving a long lasting effect.\n\tAdd a little length to your nails! SNS is the perfect product to nourish your nails while\nshowing off your new manicure!",
                 "2 hours",
                 935000)
    };
    }

    else if (pilihMenu == 3){
    categories = {
        Category("UV Gel Fullset - Short Length",
                 "Cuticle work, Extensions, file, buff and polish. UV Gel is the perfect alternative to\n\tacrylic! Lighter, more flexible and odourless! The finish can be crystal clear if you want\nthat special look or we will paint any polish of your choice. Gorgeous as gloss,\n\tlasting like diamonds. Sculpturing is available instore for �10 more. Please note that this is\nNOT PollyGel which we will not work on.",
                 "2 hours",
                 935000),
        Category("UV Gel Fullset & Shellac - Short Length",
                 "Cuticle work, Extensions, file, buff and polish. UV Gel is the perfect alternative to\n\tacrylic! Lighter, more flexible and odourless! The finish can be crystal clear if you want\n\tthat special look or Choose Shellac for that long lasting shine that you're looking for!\n\tYour gel polish will last until your next billills! Gorgeous as gloss, lasting like diamonds\nPlease note that this is NOT PollyGel which we will not work on.",
                 "2 hours 15 minutes",
                 1247000),
        Category("UV Gel Overlay",
                 "UV Gel is the perfect alternative to acrylic! Lighter, more flexible and odourless!\n\tA layer on your natural nails can make them durable and glossy just like you want them!\n\tPlease note that this is NOT PollyGel which we will not work on.",
                 "1 hour 30 minutes",
                 899000),
        Category("UV Gel Overlay & Shellac",
                 "UV Gel is the perfect alternative to acrylic! Lighter, more flexible and odourless! A layer\n\ton your natural nails can make them durable and glossy just like you want them!\n\tChoose Shellac for that long lasting shine that you're looking for! Your gel polish will\n\tlast until your next billills! You can add gel polish for a few pounds more if you want a\nmore glossy finish. Please note that this is NOT PollyGel which we will not work on.",
                 "1 hour 40 minutes",
                 1101000)
    };
    }

    else if (pilihMenu == 4){
    categories = {
        Category("Gel Powder Fullset with tips - Short Length",
                 "Cuticle work, Extensions, file, buff and polish. It will strengthen and lengthen\n\tyour nails but with a transparent finish hich is ideal for light colors or french manicures.\n\tWhy not opt for gel polish to give you that longer-lasting durable finish!",
                 "1 hour 15 minutes",
                 907000),
        Category("Gel Powder Fullset with tips & Shellac - Short Length",
                 "Cuticle work, Extensions, file, buff and Gel polish. In addition to your beautiful\n\tand durable set of Gel Powder nails, you can treat yourself to a long-lasting shellac\n\tcoating and a seductive shine!",
                 "1 hour 25 minutes",
                 1101000),
        Category("Gel Powder Overlay",
                 "Cuticle work, cut, overlay, file, buff, and polish. A great alternative to acrylic\n\toverlay to make your natural nails stronger without adding length! You just need to pick\n\ttone of our nail varnishes to complete your look!",
                 "1 hour",
                 821000),
        Category("Gel Powder Overlay & Shellac",
                 "Cuticle work, cut, file, overlay, buff, and Gel polish. For all the gel polish lovers!\n\tTo keep that shine for longer on your amazing set of nails!",
                 "1 hour 10 minutes",
                 1101000)
    };
    }

    else if (pilihMenu == 5){
    categories = {
        Category("Acrylic billills",
                 "This will remedy your out � grown nails. The treatment fills out the gaps between the\n\tacrylic and the cuticles. In-order to maintain your nails. They will need to be refilled,\n\treshaped, buffed and polished every 2 � 3 weeks.",
                 "1 hour",
                 776000),
        Category("Acrylic billills with Shellac",
                 "The treatment fills out the gaps between the acrylic and the cuticles. With gel polish\n\tfor longer lasting colour! In-order to maintain your nails, they will need to be refilled,\n\treshaped, buffed and polished every 2 � 3 weeks.",
                 "1 hour 10 minutes",
                 821000),
        Category("UV Gel billills",
                 "Your perfect nail routine to keep your nails as beautiful as the first day! We recommend\n\tyou book with us for your billills every 2-3 weeks!",
                 "1 hour",
                 821000),
        Category("UV Gel billills Shellac",
                 "Your perfect nail routine to keep your nails as beautiful as the first day! We recommend\n\tyou book with us for your billills every 2-3 weeks! Make sure your polish will stay\n\tperfect with our long lasting gel polishes!",
                 "1 hour 10 minutes",
                 907000),
        Category("Ombre billills",
                 "If you love the natural look and you can't get enough of your ombre nails then this\n\ttreatment is perfect for you! Your nails\n\twill look brand new!",
                 "45 minutes",
                 821000),
        Category("SNS billills",
                 "If you love the SNS colour you've chosen there's no need to take it off for a new set!\nWe'll billill your nails for you to\n\tmake them look fresh again!",
                "1 hour",
                 821000),
        Category("SNS billills Shellac",
                 "For everyone who opted for clear SNS we got you covered! You can get your set of\n\tnails filled-in and choose the perfect colour for you from our range of long lasting\n\tgel polishes!",
                 "1 hour 10 minutes",
                 907000)
    };
    }

    else if (pilihMenu == 6){
    categories = {
        Category("Trieu Nails Deluxe Manicure",
                 "Specially designed to leave your hands feeling wonderful. This treatment consists of\n\tthe classical manicure topped with a lush hand massage.",
                 "40 minutes",
                 700000),
        Category("Express Nails & Go",
                 "Cut, file, buff and polish. This shape up is the ideal treatment if you are someone that is\n\ton the go. The most basic of manicures which still leaves your hands looking fabulous!",
                 "20 minutes",
                 350000),
        Category("Just Varnish",
                 "Nails are buffed and a colour of your choice from our selection or from home is applied",
                 "15 minutes ",
                 672000),
        Category("Express Nails & Go with Shellac/ Gel",
                 "Cut, file, buff and Gel polish. Are you in a rush but still want a flawless gel manicure?\n\tThen Express & Go Shellac is the treatment for you!",
                 "30 minutes",
                 700000),
        Category("Cuticle Oil Pen",
                 "-",
                 "1 minutes",
                 75000),
        Category("Gel Manicure with BIAB",
                 "-",
                "45 minutes",
                 821000)
    };
    }

    else if (pilihMenu == 7){
    categories = {
        Category("Express Toes & Go",
                 "Cut file shape and Polish. This is for when you want to treat your toes without too much\n\tfuss and leave you with good looking feet in half the time",
                 "20 minutes",
                 640000),
        Category("Shellac Pedicure",
                 "Looking for longevity? This shellac treatment is perfect for you. It includes everything\n\tthat the Classical Pedicure has to offer, plus the long lasting effect of the\n\tGel polish, resistant up to 4 weeks.",
                 "50 minutes",
                 909000),
        Category("Express Toes & Go Shellac",
                 "Cut, file, shape and Gel Polish. This is the normal Express Toes & go BUT your smudging\n\tday are over! As a bonus you will be on your way faster than you can spell shellac!",
                 "35 minutes ",
                 750000),
        Category("Big toe extension",
                 "Simply two big toes extensions",
                 "20 minutes",
                 350000),
    };
    }

    else if (pilihMenu == 8){
    categories = {
        Category("Take Off Only Shellac",
                 "Our technician will buff off the top coat of your existing product and soak the rest\n\tof shellac off with acetone to prevent nail damage. They will then continue to remove\n\tthe rest of the remaining product.",
                 "15 minutes",
                 200000),
        Category("Take Off Only Acrylic",
                 "-",
                 "25 minutes",
                 245000),
        Category("Take Off Only UV Gel",
                 "We will drill your UV gel down to a thin layer and then buff the rest of them off\n\twith a hand file to prevent the damage.",
                 "30 minutes ",
                 301000)
    };
    }

    lanjut(categories);
    int selectedCategory;
    cout << "\n\tChoose the number of the category you want to see details and book: ";
    cin >> selectedCategory;
    system("cls");

    //memanggil fungsi untuk menampilkan detail dari kategori yang telah dipilih client
    displayCategoryDetails(categories, selectedCategory);

    //client memilih hari appointment
    cout << "\n\tSet the date." << endl;
    string dayList[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for(int i = 0; i < 7; i++)
        {
            cout << "\t" << (i+1) <<".  " << dayList[i] << endl;
        }

    cout << "\n\tChoose number of when you want to get our treatment: " << endl;
    cout << "\n\tYour choice: ";
    int day;
    cin >> day;
    system("cls");

    string addOn; int pilihAddOnList;
    cout << "\n\tDo you want to add some other treatment to your appointment?(y/n)" << endl;
    cout << "\n\tNote: every add on will charge you Rp 75.000 but it's worth it ;)" << endl;
    cout << "\n\tYour choice: ";
    cin >> addOn;
    system("cls");

    string addOnList[] = {"Acrylic Fullset with tips & Shellac", "BIAB Base Builder Gel", "Chin Waxing", "Classical Manicure", "Classical Pedicure", "Cut Down (Natural Nails)", "Cuticle Oil Pen", "-"};
    int addOnListSize = sizeof(addOnList) / sizeof(addOnList[0]);
    double hargaAddOn;
    if (addOn == "y" || addOn == "Y"){
    for(int i = 0; i < addOnListSize-1; i++)
        {
            if (i==0){
                cout << "\n" << endl;
            }
            cout << "\t" << (i+1) <<".  " << addOnList[i] << endl;
        }
        cout << endl;
        cout << "\n\tChoose Number of the add on you want to book: ";
        cin >> pilihAddOnList;
        hargaAddOn = 75000;
        system("cls");

        cout << "\n\tBooking success" << endl;
        cout << "\n\tDirecting you to your bill" << endl;
        Sleep(2000);
        system("cls");

     } else if (addOn == "n" || addOn == "N") {
        pilihAddOnList = 8;
        hargaAddOn = 0;
        cout << "\n\tBooking success" << endl;
        cout << "\n\tAlright then we're directing you to your bill" << endl;
        Sleep(2000);
        system("cls");
     }

    double price = categories[selectedCategory - 1].price;
    double total = invoice(customer, addOnList[pilihAddOnList - 1], dayList[day - 1], hargaAddOn, price);

    //memprint invoice ke console
    printInvoice();

    //memanggil fungsi payment agar client dapat melakukan pembayaran
    payment(total);
    Sleep(1500);

    system("cls");

    return 0;
}
