#include <stdio.h>
#include <stdlib.h>

/*
 * LOI: CWE-190 - Integer Overflow
 * Ham tinh tong dung luong can cap phat = so_phan_tu * kich_thuoc_moi_phan_tu.
 * Ca hai deu la 'int' (hoac 'unsigned int'), neu gia tri dau vao du lon,
 * phep nhan se bi TRAN SO (overflow) va cho ra 1 con so nho hon that,
 * dan toi cap phat thieu bo nho -> ghi du lieu vuot qua vung da cap phat sau nay.
 */
static void *
cap_phat_mang(int so_phan_tu, int kich_thuoc_moi_phan_tu)
{
    /* LOI XAY RA O DAY: so_phan_tu * kich_thuoc_moi_phan_tu co the tran so int */
    int tong_dung_luong = so_phan_tu * kich_thuoc_moi_phan_tu;

    printf("Cap phat %d byte cho %d phan tu\n", tong_dung_luong, so_phan_tu);

    return malloc(tong_dung_luong);
}

int main(void)
{
    /* Gia lap input tu ben ngoai (vd doc tu file/config) du lon de gay overflow */
    int so_phan_tu = 1000000000;      /* 1 ty phan tu */
    int kich_thuoc_moi_phan_tu = 8;   /* moi phan tu 8 byte */

    /* 1,000,000,000 * 8 = 8,000,000,000 -> vuot gioi han int 32-bit (~2.1 ty)
       -> tran so, ket qua sai lech hoan toan so voi dung luong thuc can */
    void *bo_nho = cap_phat_mang(so_phan_tu, kich_thuoc_moi_phan_tu);

    if (bo_nho == NULL) {
        printf("Cap phat that bai\n");
        return 1;
    }

    free(bo_nho);
    return 0;
}