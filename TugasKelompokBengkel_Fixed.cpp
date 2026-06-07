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

string keUnderscore(string teks) {
	for (size_t i = 0; i < teks.length(); i++) {
		if (teks[i] == ' ') teks[i] = '_';
	}
	return teks;
}

string keSpasi(string teks) {
	for (size_t i = 0; i < teks.length(); i++) {
		if (teks[i] == '_') teks[i] = ' ';
	}
	return teks;
}

void muatDataPelanggan(Pelanggan db[], int *jml) {
	ifstream file("Database/pelanggan.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && file >> db[*jml].id) {
			file >> db[*jml].nama;   db[*jml].nama = keSpasi(db[*jml].nama);
			file >> db[*jml].telp;
			file >> db[*jml].alamat; db[*jml].alamat = keSpasi(db[*jml].alamat);
			(*jml)++;
		}
		file.close();
	}
}

void simpanDataPelanggan(Pelanggan db[], int jml) {
	ofstream file("Database/pelanggan.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << " " 
			 << keUnderscore(db[i].nama) << " " 
			 << db[i].telp << " " 
			 << keUnderscore(db[i].alamat) << "\n";
	}
	file.close();
}

void muatDataKendaraan(Kendaraan db[], int *jml) {
	ifstream file("Database/kendaraan.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && file >> db[*jml].id) {
			file >> db[*jml].idpel;
			file >> db[*jml].merk;  db[*jml].merk = keSpasi(db[*jml].merk);
			file >> db[*jml].nopol; db[*jml].nopol = keSpasi(db[*jml].nopol);
			file >> db[*jml].tahun;
			(*jml)++;
		}
		file.close();
	}
}

void simpanDataKendaraan(Kendaraan db[], int jml) {
	ofstream file("Database/kendaraan.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << " " 
			 << db[i].idpel << " " 
			 << keUnderscore(db[i].merk) << " " 
			 << keUnderscore(db[i].nopol) << " " 
			 << db[i].tahun << "\n";
	}
	file.close();
}

void muatDataServis(Servis db[], int *jml) {
	ifstream file("Database/servis.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && file >> db[*jml].id) {
			file >> db[*jml].idkendaraan;
			file >> db[*jml].keluhan; db[*jml].keluhan = keSpasi(db[*jml].keluhan);
			file >> db[*jml].status;  db[*jml].status = keSpasi(db[*jml].status);
			file >> db[*jml].biaya;
			(*jml)++;
		}
		file.close();
	}
}

void simpanDataServis(Servis db[], int jml) {
	ofstream file("Database/servis.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << " " 
			 << db[i].idkendaraan << " " 
			 << keUnderscore(db[i].keluhan) << " " 
			 << keUnderscore(db[i].status) << " " 
			 << fixed << setprecision(0) << db[i].biaya << "\n";
	}
	file.close();
}

void muatDataRestorasi(Restorasi db[], int *jml) {
	ifstream file("Database/restorasi.txt");
	*jml = 0;
	if (file.is_open()) {
		while (*jml < MAKS_DATA && file >> db[*jml].id) {
			file >> db[*jml].idkendaraan;
			file >> db[*jml].deskripsi; db[*jml].deskripsi = keSpasi(db[*jml].deskripsi);
			file >> db[*jml].status;    db[*jml].status = keSpasi(db[*jml].status);
			file >> db[*jml].biaya;
			(*jml)++;
		}
		file.close();
	}
}

void simpanDataRestorasi(Restorasi db[], int jml) {
	ofstream file("Database/restorasi.txt");
	for (int i = 0; i < jml; i++) {
		file << db[i].id << " " 
			 << db[i].idkendaraan << " " 
			 << keUnderscore(db[i].deskripsi) << " " 
			 << keUnderscore(db[i].status) << " " 
			 << fixed << setprecision(0) << db[i].biaya << "\n";
	}
	file.close();
}

void tambahPelanggan(Pelanggan db[], int *jml) {
	if (*jml >= MAKS_DATA) {
		cout << "Kapasitas penuh!\n"; return;
	}
	bool duplikat;
	do {
		duplikat = false;
		cout << "\nID Pelanggan : "; cin >> db[*jml].id;
		for (int i = 0; i < *jml; i++) {
			if (db[i].id == db[*jml].id) {
				cout << "  [ERROR] ID Pelanggan sudah digunakan! Masukkan ID lain.\n";
				duplikat = true;
				break;
			}
		}
	} while (duplikat);

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

void hapusPelanggan(Pelanggan db[], int *jml) {
	string idHapus;
	cout << "\nMasukkan ID Pelanggan yang akan dihapus: ";
	cin >> idHapus;
	bool ketemu = false;

	for (int i = 0; i < *jml; i++) {
		if (db[i].id == idHapus) {
			ketemu = true;
			for (int j = i; j < *jml - 1; j++) {
				db[j] = db[j + 1];
			}
			(*jml)--;
			cout << "Data pelanggan berhasil dihapus!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data pelanggan tidak ditemukan.\n";
}

void menuPelanggan(Pelanggan db[], int *jml) {
	int pilih;
	do {
		cout << "\n=== MENU PELANGGAN ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Cari\n4. Hapus\n0. Kembali\nPilih : ";
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
			case 4: hapusPelanggan(db, jml); break;
		}
	} while(pilih != 0);
}

void tambahKendaraan(Kendaraan db[], int *jml, Pelanggan dbPel[], int jmlPel) {
	if (*jml >= MAKS_DATA) return;
	bool duplikat;
	do {
		duplikat = false;
		cout << "\nID Kendaraan : "; cin >> db[*jml].id;
		for (int i = 0; i < *jml; i++) {
			if (db[i].id == db[*jml].id) {
				cout << "  [ERROR] ID Kendaraan sudah digunakan! Masukkan ID lain.\n";
				duplikat = true;
				break;
			}
		}
	} while (duplikat);
	
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

void hapusKendaraan(Kendaraan db[], int *jml) {
	string idHapus;
	cout << "\nMasukkan ID Kendaraan yang akan dihapus: ";
	cin >> idHapus;
	bool ketemu = false;

	for (int i = 0; i < *jml; i++) {
		if (db[i].id == idHapus) {
			ketemu = true;
			for (int j = i; j < *jml - 1; j++) {
				db[j] = db[j + 1];
			}
			(*jml)--;
			cout << "Data kendaraan berhasil dihapus!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data kendaraan tidak ditemukan.\n";
}

void menuKendaraan(Kendaraan db[], int *jml, Pelanggan dbPel[], int jmlPel) {
	int p;
	do {
		cout << "\n=== MENU KENDARAAN ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Hapus\n0. Kembali\nPilih : ";
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
			case 3: hapusKendaraan(db, jml); break;
		}
	} while(p != 0);
}

void tambahServis(Servis db[], int *jml, Kendaraan dbKen[], int jmlKen) {
	if (*jml >= MAKS_DATA) return;
	
	bool duplikat;
	do {
		duplikat = false;
		cout << "\nID Servis    : "; cin >> db[*jml].id;
		for (int i = 0; i < *jml; i++) {
			if (db[i].id == db[*jml].id) {
				cout << "  [ERROR] ID Servis sudah digunakan! Masukkan ID lain.\n";
				duplikat = true;
				break;
			}
		}
	} while (duplikat);
	cin.ignore();
	
	bool kenKetemu = false;
	do {
		cout << "ID Kendaraan (ketik 0 untuk batal): "; getline(cin, db[*jml].idkendaraan);
		if (db[*jml].idkendaraan == "0") {
			cout << "\n[INFO] Penambahan data servis dibatalkan.\n";
			return; 
		}

		for (int i = 0; i < jmlKen; i++) {
			if (dbKen[i].id == db[*jml].idkendaraan) {
				kenKetemu = true;
				cout << "  -> Kendaraan Ditemukan: " << dbKen[i].merk << " (" << dbKen[i].nopol << ")\n"; 
				break;
			}
		}
		if (!kenKetemu) {
			cout << "  [ERROR] ID Kendaraan tidak terdaftar! Harap masukkan ID yang valid.\n";
		}
	} while (!kenKetemu);

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
	if (jml == 0) cout << "Belum ada data.\n";
	for (int i = 0; i < jml; i++) {
		cout << db[i].id << " | Kendaraan: " << db[i].idkendaraan 
			 << " | Rp" << fixed << setprecision(0) << db[i].biaya << " | Status: " << db[i].status << endl;
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

void ubahStatusServis(Servis db[], int jml) {
	string idUbah;
	cout << "\nMasukkan ID Servis yang akan diubah statusnya: ";
	cin >> idUbah;
	bool ketemu = false;

	for (int i = 0; i < jml; i++) {
		if (db[i].id == idUbah) {
			ketemu = true;
			cout << "Status saat ini : " << db[i].status << "\n";
			cin.ignore();
			cout << "Status baru     : ";
			getline(cin, db[i].status);
			cout << "Status berhasil diperbarui!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data servis tidak ditemukan.\n";
}

void hapusServis(Servis db[], int *jml) {
	string idHapus;
	cout << "\nMasukkan ID Servis yang akan dihapus: ";
	cin >> idHapus;
	bool ketemu = false;

	for (int i = 0; i < *jml; i++) {
		if (db[i].id == idHapus) {
			ketemu = true;
			for (int j = i; j < *jml - 1; j++) {
				db[j] = db[j + 1];
			}
			(*jml)--;
			cout << "Data servis berhasil dihapus!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data servis tidak ditemukan.\n";
}

void menuServis(Servis db[], int *jml, Kendaraan dbKen[], int jmlKen) {
	int p;
	do {
		cout << "\n=== MENU SERVIS ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Urutkan berdasar Biaya\n4. Ubah Status\n5. Hapus\n0. Kembali\nPilih : ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			p = -1;
			continue;
		}
		switch(p) {
			case 1: tambahServis(db, jml, dbKen, jmlKen); break;
			case 2: lihatServis(db, *jml); break;
			case 3: urutkanServis(db, *jml); break;
			case 4: ubahStatusServis(db, *jml); break;
			case 5: hapusServis(db, jml); break;
		}
	} while(p != 0);
}

void tambahRestorasi(Restorasi db[], int *jml, Kendaraan dbKen[], int jmlKen) {
	if (*jml >= MAKS_DATA) return;
	
	bool duplikat;
	do {
		duplikat = false;
		cout << "\nID Restorasi : "; cin >> db[*jml].id;
		for (int i = 0; i < *jml; i++) {
			if (db[i].id == db[*jml].id) {
				cout << "  [ERROR] ID Restorasi sudah digunakan! Masukkan ID lain.\n";
				duplikat = true;
				break;
			}
		}
	} while (duplikat);

	cin.ignore();

	bool kenKetemu = false;
	do {
		cout << "ID Kendaraan (ketik 0 untuk batal): "; getline(cin, db[*jml].idkendaraan);
		if (db[*jml].idkendaraan == "0") {
			cout << "\n[INFO] Penambahan data restorasi dibatalkan.\n";
			return; 
		}

		for (int i = 0; i < jmlKen; i++) {
			if (dbKen[i].id == db[*jml].idkendaraan) {
				kenKetemu = true;
				cout << "  -> Kendaraan Ditemukan: " << dbKen[i].merk << " (" << dbKen[i].nopol << ")\n"; 
				break;
			}
		}
		if (!kenKetemu) {
			cout << "  [ERROR] ID Kendaraan tidak terdaftar! Harap masukkan ID yang valid.\n";
		}
	} while (!kenKetemu);

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
			 << db[i].deskripsi << " | Rp" << fixed << setprecision(0) << db[i].biaya << " | Status: " << db[i].status << endl;
	}
}

void ubahStatusRestorasi(Restorasi db[], int jml) {
	string idUbah;
	cout << "\nMasukkan ID Restorasi yang akan diubah statusnya: ";
	cin >> idUbah;
	bool ketemu = false;

	for (int i = 0; i < jml; i++) {
		if (db[i].id == idUbah) {
			ketemu = true;
			cout << "Status saat ini : " << db[i].status << "\n";
			cin.ignore();
			cout << "Status baru     : ";
			getline(cin, db[i].status);
			cout << "Status berhasil diperbarui!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data restorasi tidak ditemukan.\n";
}

void hapusRestorasi(Restorasi db[], int *jml) {
	string idHapus;
	cout << "\nMasukkan ID Restorasi yang akan dihapus: ";
	cin >> idHapus;
	bool ketemu = false;

	for (int i = 0; i < *jml; i++) {
		if (db[i].id == idHapus) {
			ketemu = true;
			for (int j = i; j < *jml - 1; j++) {
				db[j] = db[j + 1];
			}
			(*jml)--;
			cout << "Data restorasi berhasil dihapus!\n";
			break;
		}
	}
	if (!ketemu) cout << "Data restorasi tidak ditemukan.\n";
}

void menuRestorasi(Restorasi db[], int *jml, Kendaraan dbKen[], int jmlKen) {
	int p;
	do {
		cout << "\n=== MENU RESTORASI ===\n";
		cout << "1. Tambah\n2. Lihat\n3. Ubah Status\n4. Hapus\n0. Kembali\nPilih : ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[ERROR] Input tidak valid! Harap masukkan ANGKA.\n";
			p = -1;
			continue;
		}
		switch(p) {
			case 1: tambahRestorasi(db, jml, dbKen, jmlKen); break;
			case 2: lihatRestorasi(db, *jml); break;
			case 3: ubahStatusRestorasi(db, *jml); break;
			case 4: hapusRestorasi(db, jml); break;
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
			case 3: menuServis(dbServis, &jmlServis, dbKendaraan, jmlKendaraan); break;
			case 4: menuRestorasi(dbRestorasi, &jmlRestorasi, dbKendaraan, jmlKendaraan); break;
			case 0: 
				simpanDataPelanggan(dbPelanggan, jmlPelanggan);
				simpanDataServis(dbServis, jmlServis);
				simpanDataKendaraan(dbKendaraan, jmlKendaraan);
				simpanDataRestorasi(dbRestorasi, jmlRestorasi);
				cout << "Seluruh data berhasil disimpan ke folder Database (format .txt spasi)!\n";
				break;
		}
	} while(pilih != 0);

	return 0;
}