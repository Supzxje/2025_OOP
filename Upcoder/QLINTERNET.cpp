#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Lớp cơ sở
class KhachHang {
protected:
    string hoTen;
    int thoiGianSuDung;
    int soMaySuDung;
    static int donGia; // đơn giá chung
public:
    KhachHang() : hoTen(""), thoiGianSuDung(0), soMaySuDung(0) {}
    KhachHang(string ten, int tg, int sm) : hoTen(ten), thoiGianSuDung(tg), soMaySuDung(sm) {}
    virtual ~KhachHang() {}
    virtual void hienThiThongTin() = 0;
    virtual int tinhTien() = 0;

    static void setDonGia(int gia) {
        donGia = gia;
    }
};

int KhachHang::donGia = 0;

// Lớp khách VIP
class KhachVIP : public KhachHang {
private:
    static int donGiaVIP;
public:
    KhachVIP() : KhachHang() {}
    KhachVIP(string ten, int tg, int sm) : KhachHang(ten, tg, sm) {}

    static void setDonGiaVIP(int gia) {
        donGiaVIP = gia;
    }

    void hienThiThongTin() override {
        cout << "Loai khach: VIP\n";
        cout << "Ho Ten: " << hoTen << endl;
        cout << "Thoi gian su dung: " << thoiGianSuDung << endl;
        cout << "So may: " << soMaySuDung << endl;
        cout << "So tien phai tra: " << tinhTien() << endl;
    }

    int tinhTien() override {
        if (thoiGianSuDung >= 4)
            return donGiaVIP * 4;
        else
            return donGia * thoiGianSuDung;
    }
};

int KhachVIP::donGiaVIP = 0;

// Lớp khách thường xuyên
class KhachThuongXuyen : public KhachHang {
private:
    int heSoKhuyenMai;
public:
    KhachThuongXuyen() : KhachHang(), heSoKhuyenMai(0) {}
    KhachThuongXuyen(string ten, int tg, int sm, int hskm) : KhachHang(ten, tg, sm), heSoKhuyenMai(hskm) {}

    void hienThiThongTin() override {
        cout << "Loai khach: TX\n";
        cout << "Ho Ten: " << hoTen << endl;
        cout << "Thoi gian su dung: " << thoiGianSuDung << endl;
        cout << "So may: " << soMaySuDung << endl;
        cout << "So tien phai tra: " << tinhTien() << endl;
    }

    int tinhTien() override {
        return thoiGianSuDung * (donGia - heSoKhuyenMai);
    }
};

// Lớp khách không thường xuyên
class KhachKhongThuongXuyen : public KhachHang {
private:
    int dungLuongDownload;
    static int donGiaDownload;
public:
    KhachKhongThuongXuyen() : KhachHang(), dungLuongDownload(0) {}
    KhachKhongThuongXuyen(string ten, int tg, int sm, int dldl) : KhachHang(ten, tg, sm), dungLuongDownload(dldl) {}

    static void setDonGiaDownload(int gia) {
        donGiaDownload = gia;
    }

    void hienThiThongTin() override {
        cout << "Loai khach: KTX\n";
        cout << "Ho Ten: " << hoTen << endl;
        cout << "Thoi gian su dung: " << thoiGianSuDung << endl;
        cout << "So may: " << soMaySuDung << endl;
        cout << "So tien phai tra: " << tinhTien() << endl;
    }

    int tinhTien() override {
        return thoiGianSuDung * donGia + dungLuongDownload * donGiaDownload;
    }
};

int KhachKhongThuongXuyen::donGiaDownload = 0;

// Hàm chính
int main() {
    int N, dg, dgVIP, dgDL;
    cin >> N >> dg >> dgVIP >> dgDL;
    KhachHang::setDonGia(dg);
    KhachVIP::setDonGiaVIP(dgVIP);
    KhachKhongThuongXuyen::setDonGiaDownload(dgDL);

    vector<KhachHang*> danhSach;
    string loai;
    cin.ignore();

    for (int i = 0; i < N; i++) {
        getline(cin, loai);
        string ten;
        int tg, sm;
        getline(cin, ten);
        cin >> tg;
        cin >> sm;
        if (loai == "VIP") {
            KhachHang* kh = new KhachVIP(ten, tg, sm);
            danhSach.push_back(kh);
        }
        else if (loai == "TX") {
            int hskm;
            cin >> hskm;
            KhachHang* kh = new KhachThuongXuyen(ten, tg, sm, hskm);
            danhSach.push_back(kh);
        }
        else if (loai == "KTX") {
            int dldl;
            cin >> dldl;
            KhachHang* kh = new KhachKhongThuongXuyen(ten, tg, sm, dldl);
            danhSach.push_back(kh);
        }
        cin.ignore();
    }

    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". ";
        danhSach[i]->hienThiThongTin();
        cout << endl;
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < N; i++) {
        delete danhSach[i];
    }

    return 0;
}