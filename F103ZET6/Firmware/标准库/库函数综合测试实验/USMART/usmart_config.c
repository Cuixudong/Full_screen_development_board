#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����)
#include "delay.h"
#include "vs10xx.h"
//#include "dm9000.h"
#include "w25qxx.h"
#include "fattester.h"
#include "bmp.h"

//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
    (void*)read_addr,"uint32_t read_addr(uint32_t addr)",
    (void*)write_addr,"void write_addr(uint32_t addr,uint32_t val)",
#endif
//	(void*)DM9000_WriteReg,"void DM9000_WriteReg(uint16_t reg,uint16_t data)",
//	(void*)DM9000_ReadReg,"uint16_t DM9000_ReadReg(uint16_t reg)",
    (void*)W25QXX_Erase_Chip,"void W25QXX_Erase_Chip(void)",
    (void*)VS_RD_Reg,"uint16_t VS_RD_Reg(uint8_t address)",
    (void*)VS_WRAM_Write,"void VS_WRAM_Write(uint16_t addr,uint16_t val)",
    (void*)VS_WRAM_Read,"uint16_t VS_WRAM_Read(uint16_t addr)",
    (void*)VS_SPK_Set,"void VS_SPK_Set(uint8_t sw)",
//  (void*)gui_show_ptstr,"void gui_show_ptstr(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint8_t size,uint8_t *str,uint8_t mode)",
    (void*)W25QXX_Erase_Chip,"void W25QXX_Erase_Chip(void)",
// 	(void*)gui_color_chg,"uint16_t gui_color_chg(uint32_t rgb)",
    (void*)bmp_encode,"uint8_t bmp_encode(uint8_t *filename,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t mode)", //0:PHOTO/PIC%04d%02d%02d%02d%02d%02d.bmp

    (void*)mf_mount,"uint8_t mf_mount(uint8_t* path,uint8_t mt)",

    (void*)mf_open,"uint8_t mf_open(uint8_t*path,uint8_t mode)",
    (void*)mf_close,"uint8_t mf_close(void)",
    (void*)mf_read,"uint8_t mf_read(uint16_t len)",
    (void*)mf_write,"uint8_t mf_write(uint8_t*dat,uint16_t len)",
    (void*)mf_opendir,"uint8_t mf_opendir(uint8_t* path)",
    (void*)mf_readdir,"uint8_t mf_readdir(void)",

    (void*)mf_scan_files,"uint32_t mf_scan_files(uint8_t * path)",
    (void*)mf_showfree,"uint32_t mf_showfree(uint8_t *drv)",
    (void*)mf_lseek,"uint8_t mf_lseek(uint32_t offset)",
    (void*)mf_tell,"uint8_t mf_tell(void)",
    (void*)mf_size,"uint32_t mf_size(void)",


    (void*)mf_fmkfs,"uint8_t mf_fmkfs(uint8_t drv,uint8_t mode,uint16_t au)",
    (void*)mf_mkdir,"uint8_t mf_mkdir(uint8_t*name)",
    (void*)mf_unlink,"uint8_t mf_unlink(uint8_t *name)",
    (void*)mf_rename,"uint8_t mf_rename(uint8_t *oldname,uint8_t* newname)",
//	(void*)SCCB_WR_Reg,"uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data)",
//	(void*)SCCB_RD_Reg,"uint8_t SCCB_RD_Reg(uint8_t reg)",
    (void*)mf_scan_files,"uint8_t mf_scan_files(uint8_t * path)",
//	(void*)ai_load_picfile,"uint8_t ai_load_picfile(const uint8_t *filename,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t fast)",

};
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
    usmart_nametab,
    usmart_init,
    usmart_cmd_rec,
    usmart_exe,
    usmart_scan,
    sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
    0,	  	//��������
    0,	 	//����ID
    1,		//������ʾ����,0,10����;1,16����
    0,		//��������.bitx:,0,����;1,�ַ���
    0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
    0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};



















