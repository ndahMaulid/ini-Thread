#include <iostream> 
//mengimpor fungsi-fungsi input/outpit stream
#include <thread>
//untuk pemrograman multithreading
#include <mutex>
//untuk mengatur penggunan sebuah resource 
#include <condition_variable>
//variabel khusus digunakan untuk menentukan kondisi tertentu sudah penuh/tidak
#include <chrono>
//library untuk memastikan tanggal dan waktu 
using namespace std;
//library standard cin, cou, end, endl

mutex Mutex;
//mutex berfungsi melindungi variabel/data tidak diakses bersamaan oleh banyak thread
//deklarasi variabel yang akan dibawa ke void
condition_variable Kondis;
//deklarasi variabel yang akan dibawa ke void
int angka = 1;
// deklarasi variabel angka dan inisialisasi variabel dengan input 1 

void oodThread() 
//fungsi yang bernama fungsi oddThread
{
    for (; angka < 20;) 
        //perulangan angka kurang dari 20 
    {
        unique_lock<mutex> manageObj(Mutex);
        //unique_lock sebuah objek yang mengelola object atau data dari mutex 
        Kondis.wait(manageObj, []() { return (angka % 2 == 1); });
        /*
        ketika variabel Kondis memeriksa penuh atau tidaknya, 
        maka akan ada jeda/menunggu untuk manageObject mengelola data, 
        jika sudah maka akan mereturn hasil loopingan dari inputan variabel angka yaitu 1  mod 2 sama dengan 1
        */
        this_thread::sleep_for(chrono::seconds(1));
        //untuk memberikan efek delay sebanyak 1 detik 
        cout << "Odd Thread: " << angka << endl;
        //untuk outputan Odd Thread sesuai angka yang telah dilooping
        angka++;
        //terus bertambah apabila outputan nilai sesuai dengan aturan looping
        Kondis.notify_all();
        /*
        variabel khusus yang mengecek penuh atau tidak, 
        juga dipakai untuk melancarkan output dari manageObj yang telah ter-unlock
        sehingga seluruh output dapat tertampilkan 
        */
    }
    
}

void evenThread()
//fungsi yang bernama fungsi evenThread
{
    for (; angka < 20;)
        //perulangan angka kurang dari 20 
    {
        unique_lock <mutex> manageObj(Mutex);
        //unique_lock sebuah objek yang mengelola object atau data dari mutex 
        Kondis.wait(manageObj, []() { return (angka % 2 == 0); });
        /*
        ketika variabel Kondis memeriksa penuh atau tidaknya,
        maka akan ada jeda/menunggu untuk manageObject mengelola data,
        jika sudah maka akan mereturn hasil loopingan dari inputan variabel angka yaitu 1  mod 2 sama dengan 1
        */
        this_thread::sleep_for(chrono::duration<float>(2.5));
        /*untuk memberikan efek delay sebanyak 2.5 detik,
        karena 2.5 bertipe data double maka code yang digunakan 
        khusus untuk double "duration<double>
        */
        cout << "Even Thread: " << angka << endl;
        //untuk outputan Even Thread sesuai angka yang telah dilooping
        angka++;
        //terus bertambah apabila outputan nilai sesuai dengan aturan looping
        manageObj.unlock();
        // pengelolaan data akan terbuka, siap menjadi output
        Kondis.notify_all();
        /*
        variabel khusus yang mengecek penuh atau tidak,
        juga dipakai untuk melancarkan output dari manageObj yang telah ter-unlock
        sehingga seluruh output dapat tertampilkan
        */
    }
}

int main()
//fungsi utama yang memberikan nilai balik menurut type datanya. 
{
    thread t_ood(oodThread);
    //memanggil fungsi oddThread
    thread t_even(evenThread);
    //memanggil fungsi oddThread
    t_ood.join();
    /*
    .join() adalah method dari thread yang berfungsi 
    miskonsepsi atau error di kode, jika tida pakai ini maka akan error otomatis
    */
    t_even.join();
    /*
    .join() adalah method dari thread yang berfungsi
    miskonsepsi atau error di kode, jika tida pakai ini maka akan error otomatis
    */
    return 0;
   //kembali ke fitrah
}