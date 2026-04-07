// --- DEFINISI PIN TRAFFIC LIGHT ---
const int tlHijau = 4;
const int tlKuning = 5;
const int tlMerah = 6;

// --- DEFINISI PIN PEDESTRIAN KIRI ---
const int pedKiriHijau = 9;
const int pedKiriMerah = 10;
const int btnKiri = 2; 

// --- DEFINISI PIN PEDESTRIAN KANAN ---
const int pedKananHijau = 7;
const int pedKananMerah = 8;
const int btnKanan = 3; 

const int waktuMenyeberang = 5000; // Waktu pejalan kaki menyeberang (5 detik)

// Variabel flag untuk menandai interupsi.
volatile bool tombolDitekan = false; 

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

  // Sintaks Interrupt
  attachInterrupt(digitalPinToInterrupt(btnKiri), isrMenyeberang, RISING);
  attachInterrupt(digitalPinToInterrupt(btnKanan), isrMenyeberang, RISING);
}

// Kondisi Awal (Kendaraan Hijau, Pedestrian Merah)
void setKondisiAwal() {
  digitalWrite(tlMerah, LOW);
  digitalWrite(tlKuning, LOW);
  digitalWrite(tlHijau, HIGH);

  digitalWrite(pedKiriMerah, HIGH);
  digitalWrite(pedKiriHijau, LOW);
  digitalWrite(pedKananMerah, HIGH);
  digitalWrite(pedKananHijau, LOW);
}

// Fungsi ISR (Interrupt Service Routine)
void isrMenyeberang() {
  tombolDitekan = true;
}

void loop() {
  if (tombolDitekan == true) {
    
    // FASE 1: PERSIAPAN BERHENTI (Tombol Ditekan)
    // Matikan lampu hijau kendaraan
    digitalWrite(tlHijau, LOW);
    
    // Efek lampu kuning kedip 3 kali sebelum merah menyala
    for (int i = 0; i < 3; i++) {
      digitalWrite(tlKuning, HIGH);
      delay(300); // Menyala 300ms
      digitalWrite(tlKuning, LOW);
      delay(300); // Mati 300ms
    }

    // FASE 2: MENYEBERANG
    // Lampu kendaraan merah, pedestrian hijau
    digitalWrite(tlMerah, HIGH);
    digitalWrite(pedKiriMerah, LOW);
    digitalWrite(pedKiriHijau, HIGH);
    digitalWrite(pedKananMerah, LOW);
    digitalWrite(pedKananHijau, HIGH);
    
    // Waktu pejalan kaki menyeberang
    delay(waktuMenyeberang);

    // FASE 3: PERSIAPAN JALAN KEMBALI
    // Lampu pedestrian kembali merah
    digitalWrite(pedKiriHijau, LOW);
    digitalWrite(pedKiriMerah, HIGH);
    digitalWrite(pedKananHijau, LOW);
    digitalWrite(pedKananMerah, HIGH);
    
    // Matikan lampu merah kendaraan
    digitalWrite(tlMerah, LOW);
    
    // Efek lampu kuning kedip 3 kali sebelum hijau menyala
    for (int i = 0; i < 3; i++) {
      digitalWrite(tlKuning, HIGH);
      delay(300); // Menyala 300ms
      digitalWrite(tlKuning, LOW);
      delay(300); // Mati 300ms
    }

    // FASE 4: SISTEM KEMBALI NORMAL
    setKondisiAwal(); // Memastikan lampu hijau menyala dan kuning mati
    
    delay(1000); // Jeda pengaman agar tidak pemicuan ganda
    tombolDitekan = false; // Reset flag interrupt
  }
}
