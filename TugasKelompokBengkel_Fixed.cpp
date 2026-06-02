#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Pelanggan { string id, nama, telp, alamat; };
struct Kendaraan { string id, idpel, merk, nopol, tahun; };
struct Servis { string id, idkendaraan, keluhan, status; double biaya; };
struct Restorasi { string id, idkendaraan, deskripsi, status; double biaya; };

const int MAKS_DATA = 100;

void muatDataPelanggan(Pelanggan db[], int *jml) {
	ifstream file("pelanggan.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && getline(file, db[*jml].id)) {
			getline(file, db[*jml].nama);
			getline(file, db[*jml].telp);
			getline(file, db[*jml].alamat);
			(*jml)++;
		}
		file.close();
	}
}

void muatDataServis(Servis db[], int *jml) {
	ifstream file("servis.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && getline(file, db[*jml].id)) {
			getline(file, db[*jml].idkendaraan);
			getline(file, db[*jml].keluhan);
			file >> db[*jml].biaya;
			file.ignore();
			getline(file, db[*jml].status);
			(*jml)++;
		}
		file.close();
	}
}
void muatDataKendaraan(Kendaraan db[], int *jml) {
	ifstream file("kendaraan.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && getline(file, db[*jml].id)) {
			getline(file, db[*jml].idpel);
			getline(file, db[*jml].merk);
			getline(file, db[*jml].nopol);
			getline(file, db[*jml].tahun);
			(*jml)++;
		}
		file.close();
	}
}

void muatDataRestorasi(Restorasi db[], int *jml) {
	ifstream file("restorasi.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && getline(file, db[*jml].id)) {
			getline(file, db[*jml].idkendaraan);
			getline(file, db[*jml].deskripsi);
			file >> db[*jml].biaya;
			file.ignore();
			getline(file, db[*jml].status);
			(*jml)++;
		}
		file.close();
	}
}

void simpanDataPelanggan(Pelanggan db[], int jml) {
	ofstream file("pelanggan.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << "\n" << db[i].nama << "\n" 
			 << db[i].telp << "\n" << db[i].alamat << "\n";
	}
	file.close();
}

void simpanDataServis(Servis db[], int jml) {
	ofstream file("servis.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << "\n" << db[i].idkendaraan << "\n" 
			 << db[i].keluhan << "\n" << db[i].biaya << "\n" << db[i].status << "\n";
	}
	file.close();
}
void simpanDataKendaraan(Kendaraan db[], int jml) {
	ofstream file("kendaraan.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << "\n" << db[i].idpel << "\n" 
			 << db[i].merk << "\n" << db[i].nopol << "\n" << db[i].tahun << "\n";
	}
	file.close();
}

void simpanDataRestorasi(Restorasi db[], int jml) {
	ofstream file("restorasi.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << "\n" << db[i].idkendaraan << "\n" 
			 << db[i].deskripsi << "\n" << db[i].biaya << "\n" << db[i].status << "\n";
	}
	file.close();
}

void tambahPelanggan(Pelanggan db[], int *jml) {
	if (*jml >= MAKS_DATA) {
		cout << "Kapasitas penuh!\n"; return;
	}
	cout << "\nID Pelanggan : "; cin >> db[*jml].id;
	cin.ignore();
	cout << "Nama         : "; getline(cin, db[*jml].nama);
	cout << "Telepon      : "; getline(cin, db[*jml].telp);
	cout << "Alamat       : "; getline(cin, db[*jml].alamat);
	
	(*jml)++;
	cout << "\nData berhasil ditambahkan!\n";
}

void lihatPelanggan(Pelanggan db[], int jml) {
	cout << "\n===== DATA PELANGGAN =====\n";
	if (jml == 0) cout << "Belum ada data.\n";
	for (int i = 0; i < jml; i++) {
		cout << db[i].id << " | " << db[i].nama << " | " << db[i].telp << " | " << db[i].alamat << endl;
	}
}

void cariPelanggan(Pelanggan db[], int jml) {
	string cari;
	cout << "\nMasukkan ID Pelanggan : ";
	cin >> cari;
	bool ketemu = false;

	for (int i = 0; i < jml; i++) {
		if (db[i].id == cari) {
			cout << "\n[DATA DITEMUKAN]\n";
			cout << "Nama   : " << db[i].nama << "\n";
			cout << "Telp   : " << db[i].telp << "\n";
			cout << "Alamat : " << db[i].alamat << "\n";
			ketemu = true;
			break;
		}
	}
	if (!ketemu) cout << "Data pelanggan tidak ditemukan.\n";
}

void menuPelanggan(Pelanggan db[], int *jml) {
	int pilih;
	do {
		cout << "\n=== MENU PELANGGAN ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Cari\n0. Kembali\nPilih : ";
		cin >> pilih;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			pilih = -1;
			continue;
		}
		switch(pilih) {
			case 1: tambahPelanggan(db, jml); break;
			case 2: lihatPelanggan(db, *jml); break;
			case 3: cariPelanggan(db, *jml); break;
		}
	} while(pilih != 0);
}

void tambahServis(Servis db[], int *jml) {
	if (*jml >= MAKS_DATA) return;
	cout << "\nID Servis    : "; cin >> db[*jml].id;
		cin.ignore();
	cout << "ID Kendaraan : "; getline(cin, db[*jml].idkendaraan);
	cout << "Keluhan      : "; getline(cin, db[*jml].keluhan);
	cout << "Biaya        : "; cin >> db[*jml].biaya;
	while (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "[ERROR] Biaya harus berupa angka! Silakan masukkan lagi.\n";
    cout << "Biaya        : "; 
    cin >> db[*jml].biaya;
}
	cin.ignore();
	cout << "Status       : "; getline(cin, db[*jml].status);
	
	(*jml)++;
	cout << "Data servis tersimpan di memori!\n";
}

void lihatServis(Servis db[], int jml) {
	cout << "\n===== DATA SERVIS =====\n";
	for (int i = 0; i < jml; i++) {
		cout << db[i].id << " | Kendaraan: " << db[i].idkendaraan 
			 << " | Rp" << fixed << setprecision(0) << db[i].biaya << " | " << db[i].status << endl;
	}
}

void urutkanServis(Servis db[], int jml) {
	for (int i = 0; i < jml - 1; i++) {
		for (int j = 0; j < jml - i - 1; j++) {
			if (db[j].biaya < db[j+1].biaya) {
				Servis temp = db[j];
				db[j] = db[j+1];
				db[j+1] = temp;
			}
		}
	}
	cout << "\n[Data telah diurutkan dari biaya tertinggi]\n";
	lihatServis(db, jml);
}

void menuServis(Servis db[], int *jml) {
	int p;
	do {
		cout << "\n=== MENU SERVIS ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Urutkan berdasar Biaya\n0. Kembali\nPilih : ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			p = -1;
			continue;
		}
		switch(p) {
			case 1: tambahServis(db, jml); break;
			case 2: lihatServis(db, *jml); break;
			case 3: urutkanServis(db, *jml); break;
		}
	} while(p != 0);
}

void tambahKendaraan(Kendaraan db[], int *jml, Pelanggan dbPel[], int jmlPel) {
	if (*jml >= MAKS_DATA) return;
	cout << "\nID Kendaraan : "; cin >> db[*jml].id;
	
	bool pelKetemu = false;
	do {
		cout << "ID Pelanggan (ketik 0 untuk batal): "; cin >> db[*jml].idpel;
		
		if (db[*jml].idpel == "0") {
			cout << "\n[INFO] Penambahan data kendaraan dibatalkan.\n";
			return;
		}

		for (int i = 0; i < jmlPel; i++) {
			if (dbPel[i].id == db[*jml].idpel) {
				pelKetemu = true;
				cout << "  -> Pemilik Ditemukan: " << dbPel[i].nama << "\n"; 
				break;
			}
		}
		if (!pelKetemu) {
			cout << "  [ERROR] ID Pelanggan tidak terdaftar! Harap masukkan ID yang valid.\n";
		}
	} while (!pelKetemu);

	cin.ignore();
	cout << "Merk/Tipe    : "; getline(cin, db[*jml].merk);
	cout << "No Polisi    : "; getline(cin, db[*jml].nopol);
	cout << "Tahun        : "; getline(cin, db[*jml].tahun);
	
	(*jml)++;
	cout << "Data kendaraan berhasil ditambahkan!\n";
}

void lihatKendaraan(Kendaraan db[], int jml, Pelanggan dbPel[], int jmlPel) {
	cout << "\n===== DATA KENDARAAN =====\n";
	if (jml == 0) cout << "Belum ada data.\n";
	for (int i = 0; i < jml; i++) {

		string namaPemilik = "Tidak Diketahui";
		for (int j = 0; j < jmlPel; j++) {
			if (dbPel[j].id == db[i].idpel) {
				namaPemilik = dbPel[j].nama;
				break;
			}
		}
		
		cout << db[i].id << " | Pemilik: " << namaPemilik << " (ID: " << db[i].idpel << ") | " 
			 << db[i].merk << " | " << db[i].nopol << " | " << db[i].tahun << endl;
	}
}

void menuKendaraan(Kendaraan db[], int *jml, Pelanggan dbPel[], int jmlPel) {
	int p;
	do {
		cout << "\n=== MENU KENDARAAN ===\n";
		cout << "1. Tambah\n2. Lihat\n0. Kembali\nPilih : ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			p = -1;
			continue;
		}
		switch(p) {
			case 1: tambahKendaraan(db, jml, dbPel, jmlPel); break; 
			case 2: lihatKendaraan(db, *jml, dbPel, jmlPel); break;
		}
	} while(p != 0);
}

void tambahRestorasi(Restorasi db[], int *jml) {
	if (*jml >= MAKS_DATA) return;
	cout << "\nID Restorasi : "; cin >> db[*jml].id;
		cin.ignore();
	cout << "ID Kendaraan : "; getline(cin, db[*jml].idkendaraan);
	cout << "Deskripsi    : "; getline(cin, db[*jml].deskripsi);
	cout << "Biaya/Est    : "; cin >> db[*jml].biaya;
	while (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "[ERROR] Biaya harus berupa angka! Silakan masukkan lagi.\n";
    cout << "Biaya        : "; 
    cin >> db[*jml].biaya;
}
	cin.ignore();
	cout << "Status       : "; getline(cin, db[*jml].status);
	
	(*jml)++;
	cout << "Data restorasi berhasil ditambahkan!\n";
}

void lihatRestorasi(Restorasi db[], int jml) {
	cout << "\n===== DATA RESTORASI =====\n";
	if (jml == 0) cout << "Belum ada data.\n";
	for (int i = 0; i < jml; i++) {
		cout << db[i].id << " | Kendaraan ID: " << db[i].idkendaraan << " | " 
			 << db[i].deskripsi << " | Rp" << fixed << setprecision(0) << db[i].biaya << " | " << db[i].status << endl;
	}
}

void menuRestorasi(Restorasi db[], int *jml) {
	int p;
	do {
		cout << "\n=== MENU RESTORASI ===\n";
		cout << "1. Tambah\n2. Lihat\n0. Kembali\nPilih : ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			p = -1;
			continue;
		}
		switch(p) {
			case 1: tambahRestorasi(db, jml); break;
			case 2: lihatRestorasi(db, *jml); break;
		}
	} while(p != 0);
}

int main() {
	Pelanggan dbPelanggan[MAKS_DATA]; int jmlPelanggan = 0;
	Servis dbServis[MAKS_DATA];       int jmlServis = 0;
	Kendaraan dbKendaraan[MAKS_DATA]; int jmlKendaraan = 0;
	Restorasi dbRestorasi[MAKS_DATA]; int jmlRestorasi = 0;
	
	muatDataPelanggan(dbPelanggan, &jmlPelanggan);
	muatDataServis(dbServis, &jmlServis);
	muatDataKendaraan(dbKendaraan, &jmlKendaraan);
	muatDataRestorasi(dbRestorasi, &jmlRestorasi);

	string user, pass;
	cout << "=== LOGIN ADMIN ===\n";
	cout << "Username : "; cin >> user;
	cout << "Password : "; cin >> pass;

	if (user != "jawasundagoat" || pass != "118129") {
		cout << "Login gagal!\n";
		return 0;
	}

	int pilih;
	do {
		cout << "\n=================================\n";
		cout << "SISTEM MANAJEMEN BENGKEL\n";
		cout << "=================================\n";
		cout << "1. Data Pelanggan\n";
		cout << "2. Data Kendaraan\n";
		cout << "3. Data Servis\n";
		cout << "4. Data Restorasi\n";
		cout << "0. Simpan & Keluar\n";
		cout << "Pilih : ";
		cin >> pilih;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			pilih = -1;
			continue;
		}
		switch(pilih) {
			case 1: menuPelanggan(dbPelanggan, &jmlPelanggan); break;
			case 2: menuKendaraan(dbKendaraan, &jmlKendaraan, dbPelanggan, jmlPelanggan); break;
			case 3: menuServis(dbServis, &jmlServis); break;
			case 4: menuRestorasi(dbRestorasi, &jmlRestorasi); break;
			case 0: 
				simpanDataPelanggan(dbPelanggan, jmlPelanggan);
				simpanDataServis(dbServis, jmlServis);
				simpanDataKendaraan(dbKendaraan, jmlKendaraan);
				simpanDataRestorasi(dbRestorasi, jmlRestorasi);
				cout << "Seluruh data berhasil disimpan ke File .txt!\n";
				break;
		}
	} while(pilih != 0);

	return 0;
}
