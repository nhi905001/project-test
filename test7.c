#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * LOI: CWE-20 - Improper Input Validation
 * Ham rut tien tu tai khoan, nhan 'so_tien' truc tiep tu nguoi dung (vd tu request API),
 * nhung KHONG kiem tra so_tien co hop le hay khong (am, qua lon, vuot so du) truoc khi
 * tru vao 'so_du'. Ke tan cong co the truyen so_tien am de LAM TANG so du thay vi giam.
 */
struct tai_khoan {
    char chu_so_huu[32];
    long so_du;
};

static int
rut_tien(struct tai_khoan *tk, long so_tien)
{
    /* LOI XAY RA O DAY: khong kiem tra so_tien > 0 va so_tien <= tk->so_du
       truoc khi thuc hien phep tru */
    tk->so_du = tk->so_du - so_tien;

    printf("Da rut %ld, so du con lai: %ld\n", so_tien, tk->so_du);
    return 0;
}

int main(void)
{
    struct tai_khoan tk;
    strncpy(tk.chu_so_huu, "Nguyen Van A", sizeof(tk.chu_so_huu) - 1);
    tk.chu_so_huu[sizeof(tk.chu_so_huu) - 1] = '\0';
    tk.so_du = 100000;

    /* Truong hop tan cong: truyen so am -> so du bi TANG len thay vi giam */
    long so_tien_yeu_cau = -500000;

    rut_tien(&tk, so_tien_yeu_cau);

    return 0;
}