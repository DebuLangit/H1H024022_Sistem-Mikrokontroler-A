// --- DEFINISI PIN ---

// 1. Arah Utara
const int utaraMerah = 13;
const int utaraKuning = 12;
const int utaraHijau = 11;

// 2. Arah Timur
const int timurMerah = 4;
const int timurKuning = 3;
const int timurHijau = 2;

// 3. Arah Selatan
const int selatanMerah = 7;
const int selatanKuning = 6;
const int selatanHijau = 5;

// 4. Arah Barat
const int baratMerah = 10;
const int baratKuning = 9;
const int baratHijau = 8;

void setup() {
  // Mengatur semua pin LED sebagai OUTPUT
  pinMode(utaraMerah, OUTPUT); pinMode(utaraKuning, OUTPUT); pinMode(utaraHijau, OUTPUT);
  pinMode(timurMerah, OUTPUT); pinMode(timurKuning, OUTPUT); pinMode(timurHijau, OUTPUT);
  pinMode(selatanMerah, OUTPUT); pinMode(selatanKuning, OUTPUT); pinMode(selatanHijau, OUTPUT);
  pinMode(baratMerah, OUTPUT); pinMode(baratKuning, OUTPUT); pinMode(baratHijau, OUTPUT);

  // Kondisi Default: Semua lampu dalam kondisi MERAH
  setSemuaMerah();
}

void loop() {
  // Berjalan terus menerus (loop) dan Searah jarum jam
  aktifkanSimpang(utaraMerah, utaraKuning, utaraHijau);
  aktifkanSimpang(timurMerah, timurKuning, timurHijau);
  aktifkanSimpang(selatanMerah, selatanKuning, selatanHijau);
  aktifkanSimpang(baratMerah, baratKuning, baratHijau);
}

// --- FUNGSI MODULAR ---

// Fungsi untuk memastikan kondisi awal jalanan terkunci (Merah semua)
void setSemuaMerah() {
  digitalWrite(utaraMerah, HIGH);   digitalWrite(utaraKuning, LOW);   digitalWrite(utaraHijau, LOW);
  digitalWrite(timurMerah, HIGH);   digitalWrite(timurKuning, LOW);   digitalWrite(timurHijau, LOW);
  digitalWrite(selatanMerah, HIGH); digitalWrite(selatanKuning, LOW); digitalWrite(selatanHijau, LOW);
  digitalWrite(baratMerah, HIGH);   digitalWrite(baratKuning, LOW);   digitalWrite(baratHijau, LOW);
}

// Fungsi utama untuk mengatur timing setiap simpang secara bergantian
void aktifkanSimpang(int pinMerah, int pinKuning, int pinHijau) {
  
  // 1. TRANSISI BARU: Merah mati, 
  digitalWrite(pinMerah, LOW);   
  // 2. Kuning menyala sebagai aba-aba (2 detik)
  digitalWrite(pinKuning, HIGH);
  delay(2000);
  digitalWrite(pinKuning, LOW); 

  // 3. Lampu Hijau menyala selama 5 detik
  digitalWrite(pinHijau, HIGH);
  delay(5000); 
  digitalWrite(pinHijau, LOW);

  // 4. Efek kedip Kuning 3 kali peringatan hijau mau habis
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinKuning, HIGH);
    delay(300); 
    digitalWrite(pinKuning, LOW);
    delay(300); 
  }

  // 5. Lampu Kuning menyala solid selama 2 detik
  digitalWrite(pinKuning, HIGH);
  delay(2000);
  digitalWrite(pinKuning, LOW);

  // 6. Kembalikan ke Lampu Merah setelah giliran selesai
  digitalWrite(pinMerah, HIGH);
}
