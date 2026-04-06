// --- DEFINISI PIN TRAFFIC LIGHT ---
const int tlHijau = 4;
const int tlKuning = 5;
const int tlMerah = 6;

// --- DEFINISI PIN PEDESTRIAN KIRI ---
const int pedKiriHijau = 2;
const int pedKiriMerah = 3;
const int btnKiri = 9;

// --- DEFINISI PIN PEDESTRIAN KANAN ---
const int pedKananHijau = 7;
const int pedKananMerah = 8;
const int btnKanan = 10;

// --- PENGATURAN WAKTU (dalam milidetik) ---
const int waktuMenyeberang = 5000; // Waktu pejalan kaki menyeberang (5 detik)
const int waktuTransisi = 2000;    // Waktu transisi lampu kuning (2 detik)

void setup() {
  // Inisialisasi pin LED sebagai OUTPUT
  pinMode(tlMerah, OUTPUT);
  pinMode(tlKuning, OUTPUT);
  pinMode(tlHijau, OUTPUT);
  
  pinMode(pedKiriMerah, OUTPUT);
  pinMode(pedKiriHijau, OUTPUT);
  
  pinMode(pedKananMerah, OUTPUT);
  pinMode(pedKananHijau, OUTPUT);

  // Inisialisasi pin Button sebagai INPUT
  pinMode(btnKiri, INPUT);
  pinMode(btnKanan, INPUT);

  // Set Kondisi Awal saat Arduino pertama kali menyala
  setKondisiAwal();
}

// Fungsi untuk mengatur sistem ke status "Default"
void setKondisiAwal() {
  // Lampu kendaraan hijau
  digitalWrite(tlMerah, LOW);
  digitalWrite(tlKuning, LOW);
  digitalWrite(tlHijau, HIGH);

  // Lampu pedestrian merah
  digitalWrite(pedKiriMerah, HIGH);
  digitalWrite(pedKiriHijau, LOW);
  digitalWrite(pedKananMerah, HIGH);
  digitalWrite(pedKananHijau, LOW);
}

void loop() {
  // Membaca status kedua tombol
  int statusBtnKiri = digitalRead(btnKiri);
  int statusBtnKanan = digitalRead(btnKanan);

  // Jika tombol kiri ATAU tombol kanan ditekan
  if (statusBtnKiri == HIGH || statusBtnKanan == HIGH) {
    
    // --------------------------------------------------
    // FASE 1: SAAT DITEKAN
    // --------------------------------------------------
    // Lampu kendaraan berubah menjadi merah
    digitalWrite(tlHijau, LOW);
    digitalWrite(tlMerah, HIGH);
    
    // Lampu pedestrian berubah menjadi hijau
    digitalWrite(pedKiriMerah, LOW);
    digitalWrite(pedKiriHijau, HIGH);
    digitalWrite(pedKananMerah, LOW);
    digitalWrite(pedKananHijau, HIGH);
    
    // Tahan kondisi ini agar pejalan kaki bisa menyeberang
    delay(waktuMenyeberang);

    // --------------------------------------------------
    // FASE 2: SETELAH WAKTU TERTENTU
    // --------------------------------------------------
    // Lampu pedestrian kembali merah
    digitalWrite(pedKiriHijau, LOW);
    digitalWrite(pedKiriMerah, HIGH);
    digitalWrite(pedKananHijau, LOW);
    digitalWrite(pedKananMerah, HIGH);
    
    // Lampu kendaraan memasuki fase kuning (transisi)
    digitalWrite(tlMerah, LOW);
    digitalWrite(tlKuning, HIGH);
    
    // Tahan kondisi transisi kuning
    delay(waktuTransisi);

    // --------------------------------------------------
    // FASE 3: SISTEM KEMBALI KE KONDISI AWAL
    // --------------------------------------------------
    // Memanggil fungsi setKondisiAwal() (Lampu kendaraan hijau, pedestrian merah)
    setKondisiAwal();
    
    // Tambahkan jeda pengaman (1 detik) agar sistem tidak langsung memicu ulang
    // jika tombol masih tidak sengaja ditahan oleh pengguna
    delay(1000); 
  }
}
