#include <stdio.h>
#include <string.h>

struct Account {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    long long final_fee;
};

int main() {
    int n;
    while (1) {
        printf("Nhap so luong tai khoan N (1 <= N <= 100): ");
        if (scanf("%d", &n) == 1 && n >= 1 && n <= 100) {
            break;
        }
        printf("Du lieu khong hop le. Vui long nhap lai!\n");
        while (getchar() != '\n');
    }

    struct Account accounts[100];
    for (int i = 0; i < n; i++) {
        while (1) {
            printf("\nNhap thong tin tai khoan thu %d:\n", i + 1);
            printf("Ma tai khoan (user_id): ");
            int uid;
            char uname[50];
            int ptype, overdue, devices;
            
            if (scanf("%d", &uid) != 1) {
                printf("Loi nhap lieu. Vui long nhap lai!\n");
                while (getchar() != '\n');
                continue;
            }
            
            printf("Ten tai khoan (username): ");
            scanf("%49s", uname);
            
            printf("Loai goi hien tai (1: Free, 2: Personal, 3: Family): ");
            if (scanf("%d", &ptype) != 1 || ptype < 1 || ptype > 3) {
                printf("Loai goi khong hop le ([1, 3]). Vui long nhap lai!\n");
                while (getchar() != '\n');
                continue;
            }
            
            printf("So ngay no cuoc (days_overdue >= 0): ");
            if (scanf("%d", &overdue) != 1 || overdue < 0) {
                printf("So ngay no cuoc khong hop le. Vui long nhap lai!\n");
                while (getchar() != '\n');
                continue;
            }
            
            printf("So thiet bi dang ket noi (active_devices >= 0): ");
            if (scanf("%d", &devices) != 1 || devices < 0) {
                printf("So thiet bi khong hop le. Vui long nhap lai!\n");
                while (getchar() != '\n');
                continue;
            }
            
            accounts[i].user_id = uid;
            strcpy(accounts[i].username, uname);
            accounts[i].plan_type = ptype;
            accounts[i].days_overdue = overdue;
            accounts[i].active_devices = devices;
            break;
        }
    }

    long long total_revenue = 0;
    int downgrade_count = 0;

    for (int i = 0; i < n; i++) {
        if (accounts[i].days_overdue >= 3) {
            if (accounts[i].plan_type != 1) {
                downgrade_count++;
            }
            accounts[i].plan_type = 1;
            accounts[i].final_fee = 0;
        } else {
            if (accounts[i].plan_type == 1) {
                accounts[i].final_fee = 0;
            } else if (accounts[i].plan_type == 2) {
                long long base_fee = 120000;
                long long surcharge = 0;
                if (accounts[i].active_devices > 1) {
                    surcharge = (long long)(accounts[i].active_devices - 1) * 30000;
                }
                accounts[i].final_fee = base_fee + surcharge;
            } else if (accounts[i].plan_type == 3) {
                accounts[i].final_fee = 250000;
            }
        }
        total_revenue += accounts[i].final_fee;
    }

    printf("\n=== BANG THONG TIN TAI KHOAN SAU RA SOAT ===\n");
    printf("%-10s | %-15s | %-10s | %-10s | %-10s | %-15s\n", "Ma TK", "Ten TK", "Ma Goi", "So Thiet Bi", "So Ngay No", "Phi Thuc Thu");
    for (int i = 0; i < 75; i++) printf("-");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%-10d | %-15s | %-10d | %-10d | %-10d | %-15lld\n",
            accounts[i].user_id,
            accounts[i].username,
            accounts[i].plan_type,
            accounts[i].active_devices,
            accounts[i].days_overdue,
            accounts[i].final_fee
        );
    }

    printf("\n=== THONG KE TONG KET ===\n");
    printf("Tong doanh thu thuc te: %lld VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap ve goi Free: %d\n", downgrade_count);

    return 0;
}
