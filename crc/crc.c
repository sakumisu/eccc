#include "crc.h"
/**

多项式产生：
如x16+x12+x5+1
x16表示第16位为1，x5表示第5位为1
(1 << 16) | (1 << 12) | (1 << 5) | (1) = 0x11021
但是CRC16只取低16位，写成16进制数就是 0x1021
*/
/**


CRC算法参数模型解释： 
    NAME：参数模型名称。 
    WIDTH：宽度，即CRC比特数。 
    POLY：生成项的简写，以16进制表示。例如：CRC-32即是0x04C11DB7，忽略了最高位的"1"，即完整的生    成项是0x104C11DB7。 
    INIT：这是算法开始时寄存器（crc）的初始化预置值，十六进制表示。 
    REFIN：待测数据的每个字节是否按位反转，True或False。 
    REFOUT：在计算后之后，异或输出之前，整个数据是否按位反转，True或False。 
    XOROUT：计算结果与此参数异或后得到最终的CRC值。
    Alias：别名及其应用范围。

*/

/*

CRC8中0x31对应0x8C，
CRC16中0X1021对应0x8408,0x8005对应0xA001

*/
#if (CRC8_POLY == 0x8C)
const uint8_t crc8_table[] = {
    0x00, 0x5E, 0xBC, 0xE2, 0x61, 0x3F, 0xDD, 0x83,
    0xC2, 0x9C, 0x7E, 0x20, 0xA3, 0xFD, 0x1F, 0x41,
    0x9D, 0xC3, 0x21, 0x7F, 0xFC, 0xA2, 0x40, 0x1E,
    0x5F, 0x01, 0xE3, 0xBD, 0x3E, 0x60, 0x82, 0xDC,
    0x23, 0x7D, 0x9F, 0xC1, 0x42, 0x1C, 0xFE, 0xA0,
    0xE1, 0xBF, 0x5D, 0x03, 0x80, 0xDE, 0x3C, 0x62,
    0xBE, 0xE0, 0x02, 0x5C, 0xDF, 0x81, 0x63, 0x3D,
    0x7C, 0x22, 0xC0, 0x9E, 0x1D, 0x43, 0xA1, 0xFF,
    0x46, 0x18, 0xFA, 0xA4, 0x27, 0x79, 0x9B, 0xC5,
    0x84, 0xDA, 0x38, 0x66, 0xE5, 0xBB, 0x59, 0x07,
    0xDB, 0x85, 0x67, 0x39, 0xBA, 0xE4, 0x06, 0x58,
    0x19, 0x47, 0xA5, 0xFB, 0x78, 0x26, 0xC4, 0x9A,
    0x65, 0x3B, 0xD9, 0x87, 0x04, 0x5A, 0xB8, 0xE6,
    0xA7, 0xF9, 0x1B, 0x45, 0xC6, 0x98, 0x7A, 0x24,
    0xF8, 0xA6, 0x44, 0x1A, 0x99, 0xC7, 0x25, 0x7B,
    0x3A, 0x64, 0x86, 0xD8, 0x5B, 0x05, 0xE7, 0xB9,
    0x8C, 0xD2, 0x30, 0x6E, 0xED, 0xB3, 0x51, 0x0F,
    0x4E, 0x10, 0xF2, 0xAC, 0x2F, 0x71, 0x93, 0xCD,
    0x11, 0x4F, 0xAD, 0xF3, 0x70, 0x2E, 0xCC, 0x92,
    0xD3, 0x8D, 0x6F, 0x31, 0xB2, 0xEC, 0x0E, 0x50,
    0xAF, 0xF1, 0x13, 0x4D, 0xCE, 0x90, 0x72, 0x2C,
    0x6D, 0x33, 0xD1, 0x8F, 0x0C, 0x52, 0xB0, 0xEE,
    0x32, 0x6C, 0x8E, 0xD0, 0x53, 0x0D, 0xEF, 0xB1,
    0xF0, 0xAE, 0x4C, 0x12, 0x91, 0xCF, 0x2D, 0x73,
    0xCA, 0x94, 0x76, 0x28, 0xAB, 0xF5, 0x17, 0x49,
    0x08, 0x56, 0xB4, 0xEA, 0x69, 0x37, 0xD5, 0x8B,
    0x57, 0x09, 0xEB, 0xB5, 0x36, 0x68, 0x8A, 0xD4,
    0x95, 0xCB, 0x29, 0x77, 0xF4, 0xAA, 0x48, 0x16,
    0xE9, 0xB7, 0x55, 0x0B, 0x88, 0xD6, 0x34, 0x6A,
    0x2B, 0x75, 0x97, 0xC9, 0x4A, 0x14, 0xF6, 0xA8,
    0x74, 0x2A, 0xC8, 0x96, 0x15, 0x4B, 0xA9, 0xF7,
    0xB6, 0xE8, 0x0A, 0x54, 0xD7, 0x89, 0x6B, 0x35
};
#elif (CRC8_POLY == 0xD9)
const uint8_t crc8_table[] = {
    0x00, 0xD0, 0x13, 0xC3, 0x26, 0xF6, 0x35, 0xE5,
    0x4C, 0x9C, 0x5F, 0x8F, 0x6A, 0xBA, 0x79, 0xA9,
    0x98, 0x48, 0x8B, 0x5B, 0xBE, 0x6E, 0xAD, 0x7D,
    0xD4, 0x04, 0xC7, 0x17, 0xF2, 0x22, 0xE1, 0x31,
    0x83, 0x53, 0x90, 0x40, 0xA5, 0x75, 0xB6, 0x66,
    0xCF, 0x1F, 0xDC, 0x0C, 0xE9, 0x39, 0xFA, 0x2A,
    0x1B, 0xCB, 0x08, 0xD8, 0x3D, 0xED, 0x2E, 0xFE,
    0x57, 0x87, 0x44, 0x94, 0x71, 0xA1, 0x62, 0xB2,
    0xB5, 0x65, 0xA6, 0x76, 0x93, 0x43, 0x80, 0x50,
    0xF9, 0x29, 0xEA, 0x3A, 0xDF, 0x0F, 0xCC, 0x1C,
    0x2D, 0xFD, 0x3E, 0xEE, 0x0B, 0xDB, 0x18, 0xC8,
    0x61, 0xB1, 0x72, 0xA2, 0x47, 0x97, 0x54, 0x84,
    0x36, 0xE6, 0x25, 0xF5, 0x10, 0xC0, 0x03, 0xD3,
    0x7A, 0xAA, 0x69, 0xB9, 0x5C, 0x8C, 0x4F, 0x9F,
    0xAE, 0x7E, 0xBD, 0x6D, 0x88, 0x58, 0x9B, 0x4B,
    0xE2, 0x32, 0xF1, 0x21, 0xC4, 0x14, 0xD7, 0x07,
    0xD9, 0x09, 0xCA, 0x1A, 0xFF, 0x2F, 0xEC, 0x3C,
    0x95, 0x45, 0x86, 0x56, 0xB3, 0x63, 0xA0, 0x70,
    0x41, 0x91, 0x52, 0x82, 0x67, 0xB7, 0x74, 0xA4,
    0x0D, 0xDD, 0x1E, 0xCE, 0x2B, 0xFB, 0x38, 0xE8,
    0x5A, 0x8A, 0x49, 0x99, 0x7C, 0xAC, 0x6F, 0xBF,
    0x16, 0xC6, 0x05, 0xD5, 0x30, 0xE0, 0x23, 0xF3,
    0xC2, 0x12, 0xD1, 0x01, 0xE4, 0x34, 0xF7, 0x27,
    0x8E, 0x5E, 0x9D, 0x4D, 0xA8, 0x78, 0xBB, 0x6B,
    0x6C, 0xBC, 0x7F, 0xAF, 0x4A, 0x9A, 0x59, 0x89,
    0x20, 0xF0, 0x33, 0xE3, 0x06, 0xD6, 0x15, 0xC5,
    0xF4, 0x24, 0xE7, 0x37, 0xD2, 0x02, 0xC1, 0x11,
    0xB8, 0x68, 0xAB, 0x7B, 0x9E, 0x4E, 0x8D, 0x5D,
    0xEF, 0x3F, 0xFC, 0x2C, 0xC9, 0x19, 0xDA, 0x0A,
    0xA3, 0x73, 0xB0, 0x60, 0x85, 0x55, 0x96, 0x46,
    0x77, 0xA7, 0x64, 0xB4, 0x51, 0x81, 0x42, 0x92,
    0x3B, 0xEB, 0x28, 0xF8, 0x1D, 0xCD, 0x0E, 0xDE
};
#endif

uint8_t crc8_cyc_cal(uint8_t init_val, uint8_t *pdata, uint32_t len)
{
    uint32_t i;
    uint8_t crc8;
    uint8_t idx;

    crc8 = init_val;
    for (i = 0; i < len; i++) {
        idx = (crc8) ^ (*pdata++);
        crc8 = crc8_table[idx];
    }

    return (crc8);
}

uint8_t crc8_cal(uint8_t *pdata, uint32_t len) //计算长度Len数量数据的CRC校验值，返回计算出的校验值
{
    return (crc8_cyc_cal(CRC8_INIT_VAL, pdata, len) ^ CRC8_INIT_VAL);
}

#if (CRC16_POLY == 0xA001)
static const uint16_t crc16_table[] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};
#elif (CRC16_POLY == 0x8408)
const uint16_t crc16_table[] = {
    0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
    0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
    0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E,
    0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876,
    0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD,
    0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5,
    0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C,
    0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974,
    0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
    0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3,
    0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A,
    0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72,
    0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9,
    0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1,
    0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738,
    0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70,
    0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7,
    0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
    0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036,
    0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E,
    0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5,
    0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD,
    0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134,
    0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C,
    0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3,
    0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB,
    0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
    0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A,
    0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1,
    0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9,
    0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330,
    0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
};
#endif

uint16_t crc16_cyc_cal(uint16_t init_val, uint8_t *pdata, uint32_t len)
{
    uint32_t i;
    uint16_t crc16;
    uint8_t idx;

    crc16 = init_val;
    for (i = 0; i < len; i++) {
        idx = ((uint8_t)crc16) ^ (*pdata++);
        crc16 = (crc16 >> 8) ^ crc16_table[idx];
    }

    return (crc16);
}

uint16_t crc16_cal(uint8_t *pdata, uint32_t len)
{
    return (crc16_cyc_cal(CRC16_INIT_VAL, pdata, len) ^ CRC16_INIT_VAL);
}

#if (CRC32_POLY == 0xEDB88320)
const uint32_t crc32_table[] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
#elif (CRC32_POLY == 0x82F63B78))
const uint32_t crc32_table[] = {
    0x00000000, 0xF26B8303, 0xE13B70F7, 0x1350F3F4, 0xC79A971F, 0x35F1141C, 0x26A1E7E8, 0xD4CA64EB,
    0x8AD958CF, 0x78B2DBCC, 0x6BE22838, 0x9989AB3B, 0x4D43CFD0, 0xBF284CD3, 0xAC78BF27, 0x5E133C24,
    0x105EC76F, 0xE235446C, 0xF165B798, 0x030E349B, 0xD7C45070, 0x25AFD373, 0x36FF2087, 0xC494A384,
    0x9A879FA0, 0x68EC1CA3, 0x7BBCEF57, 0x89D76C54, 0x5D1D08BF, 0xAF768BBC, 0xBC267848, 0x4E4DFB4B,
    0x20BD8EDE, 0xD2D60DDD, 0xC186FE29, 0x33ED7D2A, 0xE72719C1, 0x154C9AC2, 0x061C6936, 0xF477EA35,
    0xAA64D611, 0x580F5512, 0x4B5FA6E6, 0xB93425E5, 0x6DFE410E, 0x9F95C20D, 0x8CC531F9, 0x7EAEB2FA,
    0x30E349B1, 0xC288CAB2, 0xD1D83946, 0x23B3BA45, 0xF779DEAE, 0x05125DAD, 0x1642AE59, 0xE4292D5A,
    0xBA3A117E, 0x4851927D, 0x5B016189, 0xA96AE28A, 0x7DA08661, 0x8FCB0562, 0x9C9BF696, 0x6EF07595,
    0x417B1DBC, 0xB3109EBF, 0xA0406D4B, 0x522BEE48, 0x86E18AA3, 0x748A09A0, 0x67DAFA54, 0x95B17957,
    0xCBA24573, 0x39C9C670, 0x2A993584, 0xD8F2B687, 0x0C38D26C, 0xFE53516F, 0xED03A29B, 0x1F682198,
    0x5125DAD3, 0xA34E59D0, 0xB01EAA24, 0x42752927, 0x96BF4DCC, 0x64D4CECF, 0x77843D3B, 0x85EFBE38,
    0xDBFC821C, 0x2997011F, 0x3AC7F2EB, 0xC8AC71E8, 0x1C661503, 0xEE0D9600, 0xFD5D65F4, 0x0F36E6F7,
    0x61C69362, 0x93AD1061, 0x80FDE395, 0x72966096, 0xA65C047D, 0x5437877E, 0x4767748A, 0xB50CF789,
    0xEB1FCBAD, 0x197448AE, 0x0A24BB5A, 0xF84F3859, 0x2C855CB2, 0xDEEEDFB1, 0xCDBE2C45, 0x3FD5AF46,
    0x7198540D, 0x83F3D70E, 0x90A324FA, 0x62C8A7F9, 0xB602C312, 0x44694011, 0x5739B3E5, 0xA55230E6,
    0xFB410CC2, 0x092A8FC1, 0x1A7A7C35, 0xE811FF36, 0x3CDB9BDD, 0xCEB018DE, 0xDDE0EB2A, 0x2F8B6829,
    0x82F63B78, 0x709DB87B, 0x63CD4B8F, 0x91A6C88C, 0x456CAC67, 0xB7072F64, 0xA457DC90, 0x563C5F93,
    0x082F63B7, 0xFA44E0B4, 0xE9141340, 0x1B7F9043, 0xCFB5F4A8, 0x3DDE77AB, 0x2E8E845F, 0xDCE5075C,
    0x92A8FC17, 0x60C37F14, 0x73938CE0, 0x81F80FE3, 0x55326B08, 0xA759E80B, 0xB4091BFF, 0x466298FC,
    0x1871A4D8, 0xEA1A27DB, 0xF94AD42F, 0x0B21572C, 0xDFEB33C7, 0x2D80B0C4, 0x3ED04330, 0xCCBBC033,
    0xA24BB5A6, 0x502036A5, 0x4370C551, 0xB11B4652, 0x65D122B9, 0x97BAA1BA, 0x84EA524E, 0x7681D14D,
    0x2892ED69, 0xDAF96E6A, 0xC9A99D9E, 0x3BC21E9D, 0xEF087A76, 0x1D63F975, 0x0E330A81, 0xFC588982,
    0xB21572C9, 0x407EF1CA, 0x532E023E, 0xA145813D, 0x758FE5D6, 0x87E466D5, 0x94B49521, 0x66DF1622,
    0x38CC2A06, 0xCAA7A905, 0xD9F75AF1, 0x2B9CD9F2, 0xFF56BD19, 0x0D3D3E1A, 0x1E6DCDEE, 0xEC064EED,
    0xC38D26C4, 0x31E6A5C7, 0x22B65633, 0xD0DDD530, 0x0417B1DB, 0xF67C32D8, 0xE52CC12C, 0x1747422F,
    0x49547E0B, 0xBB3FFD08, 0xA86F0EFC, 0x5A048DFF, 0x8ECEE914, 0x7CA56A17, 0x6FF599E3, 0x9D9E1AE0,
    0xD3D3E1AB, 0x21B862A8, 0x32E8915C, 0xC083125F, 0x144976B4, 0xE622F5B7, 0xF5720643, 0x07198540,
    0x590AB964, 0xAB613A67, 0xB831C993, 0x4A5A4A90, 0x9E902E7B, 0x6CFBAD78, 0x7FAB5E8C, 0x8DC0DD8F,
    0xE330A81A, 0x115B2B19, 0x020BD8ED, 0xF0605BEE, 0x24AA3F05, 0xD6C1BC06, 0xC5914FF2, 0x37FACCF1,
    0x69E9F0D5, 0x9B8273D6, 0x88D28022, 0x7AB90321, 0xAE7367CA, 0x5C18E4C9, 0x4F48173D, 0xBD23943E,
    0xF36E6F75, 0x0105EC76, 0x12551F82, 0xE03E9C81, 0x34F4F86A, 0xC69F7B69, 0xD5CF889D, 0x27A40B9E,
    0x79B737BA, 0x8BDCB4B9, 0x988C474D, 0x6AE7C44E, 0xBE2DA0A5, 0x4C4623A6, 0x5F16D052, 0xAD7D5351
};
#endif

uint32_t crc32_cyc_cal(uint32_t init_val, uint8_t *pdata, uint32_t len)
{
    uint32_t i;
    uint32_t crc32;
    uint8_t idx;

    crc32 = init_val;
    for (i = 0; i < len; i++) {
        idx = ((uint8_t)crc32) ^ (*pdata++);
        crc32 = (crc32 >> 8) ^ crc32_table[idx];
    }

    return (crc32);
}

uint32_t crc32_cal(uint8_t *pdata, uint32_t len)
{
    return (crc32_cyc_cal(CRC32_INIT_VAL, pdata, len) ^ CRC32_INIT_VAL);
}

/****************************Info********************************************** 
 * Name:    InvertUint8 
 * Note: 	把字节颠倒过来，如0x12变成0x48
			0x12: 0001 0010
			0x48: 0100 1000
 *****************************************************************************/
void InvertUint8(uint8_t *dBuf, uint8_t *srcBuf)
{
    int i;
    uint8_t tmp[4] = { 0 };

    for (i = 0; i < 8; i++) {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (7 - i);
    }
    dBuf[0] = tmp[0];
}
void InvertUint16(uint16_t *dBuf, uint16_t *srcBuf)
{
    int i;
    uint16_t tmp[4] = { 0 };

    for (i = 0; i < 16; i++) {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (15 - i);
    }
    dBuf[0] = tmp[0];
}
void InvertUint32(uint32_t *dBuf, uint32_t *srcBuf)
{
    int i;
    uint32_t tmp[4] = { 0 };

    for (i = 0; i < 32; i++) {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (31 - i);
    }
    dBuf[0] = tmp[0];
}

/****************************Info********************************************** 
 * Name:    CRC-4/ITU	x4+x+1 
 * Width:	4
 * Poly:    0x03 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
uint8_t CRC4_ITU(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x03;
    uint8_t wChar = 0;

    while (datalen--) {
        wChar = *(data++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ (wCPoly << 4);
            else
                wCRCin = wCRCin << 1;
        }
    }
    InvertUint8(&wCRCin, &wCRCin);
    return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-5/EPC	x5+x3+1 
 * Width:	5
 * Poly:    0x09 
 * Init:    0x09 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
uint8_t CRC5_EPC(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x09 << 3;
    uint8_t wCPoly = 0x09 << 3;

    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ (wCPoly);
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin >> 3);
}
/****************************Info********************************************** 
 * Name:    CRC-5/USB	x5+x2+1 
 * Width:	5
 * Poly:    0x05 
 * Init:    0x1F 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x1F 
 * Note: 
 *****************************************************************************/
#if 0
uint8_t CRC5_USB(uint8_t *data, uint32_t datalen)
{
	uint8_t wCRCin = 0x1F<<3;
	uint8_t wCPoly = 0x05;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 3);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin^0x1F);
}
#else
uint8_t CRC5_USB(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x1F;
    uint8_t wCPoly = 0x05;

    InvertUint8(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ (wCPoly >> 3);
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin ^ 0x1F);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-5/ITU	x5+x4+x2+1  
 * Width:	5
 * Poly:    0x15 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
#if 0
uint8_t CRC5_ITU(uint8_t *data, uint32_t datalen)
{
	uint8_t wCRCin = 0x00;
	uint8_t wCPoly = 0x15;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 3);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
uint8_t CRC5_ITU(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x15;

    InvertUint8(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ (wCPoly >> 3);
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-6/ITU	x6+x+1 
 * Width:	6
 * Poly:    0x03 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
uint8_t CRC6_ITU(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x03;
    uint8_t wChar = 0;

    while (datalen--) {
        wChar = *(data++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ (wCPoly << 2);
            else
                wCRCin = wCRCin << 1;
        }
    }
    InvertUint8(&wCRCin, &wCRCin);
    return (wCRCin);
}

uint8_t crc7_be(uint8_t seed, const uint8_t *src, size_t len)
{
    while (len--) {
        uint8_t e = seed ^ *src++;
        uint8_t f = e ^ (e >> 4) ^ (e >> 7);

        seed = (f << 1) ^ (f << 4);
    }

    return seed;
}

/****************************Info********************************************** 
 * Name:    CRC-7/MMC           x7+x3+1  
 * Width:	7
 * Poly:    0x09 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Use:     MultiMediaCard,SD,ect. 
 *****************************************************************************/
uint8_t CRC7_MMC(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x09;

    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ (wCPoly << 1);
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin >> 1);
}

static const uint8_t crc8_ccitt_small_table[16] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
    0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d
};

uint8_t crc8_ccitt(uint8_t val, const void *buf, size_t cnt)
{
    size_t i;
    const uint8_t *p = buf;

    for (i = 0; i < cnt; i++) {
        val ^= p[i];
        val = (val << 4) ^ crc8_ccitt_small_table[val >> 4];
        val = (val << 4) ^ crc8_ccitt_small_table[val >> 4];
    }
    return val;
}

uint8_t crc8(const uint8_t *src, size_t len, uint8_t polynomial, uint8_t initial_value,
             bool reversed)
{
    uint8_t crc = initial_value;
    size_t i, j;

    for (i = 0; i < len; i++) {
        crc ^= src[i];

        for (j = 0; j < 8; j++) {
            if (reversed) {
                if (crc & 0x01) {
                    crc = (crc >> 1) ^ polynomial;
                } else {
                    crc >>= 1;
                }
            } else {
                if (crc & 0x80) {
                    crc = (crc << 1) ^ polynomial;
                } else {
                    crc <<= 1;
                }
            }
        }
    }

    return crc;
}

/****************************Info********************************************** 
 * Name:    CRC-8               x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
uint8_t CRC8(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x07;

    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-8/ITU           x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x55 
 * Alias:   CRC-8/ATM 
 *****************************************************************************/
uint8_t CRC8_ITU(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x07;

    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin ^ 0x55);
}
/****************************Info********************************************** 
 * Name:    CRC-8/ROHC          x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0xFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
#if 0
uint8_t CRC8_ROHC(uint8_t *data, uint32_t datalen)
{
	uint8_t wCRCin = 0xFF;
	uint8_t wCPoly = 0x07;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 0);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
uint8_t CRC8_ROHC(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0xFF;
    uint8_t wCPoly = 0x07;

    InvertUint8(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-8/MAXIM         x8+x5+x4+1 
 * Width:	8 
 * Poly:    0x31 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Alias:   DOW-CRC,CRC-8/IBUTTON 
 * Use:     Maxim(Dallas)'s some devices,e.g. DS18B20 
 *****************************************************************************/
#if 0
uint8_t CRC8_MAXIM(uint8_t *data, uint32_t datalen)
{
	uint8_t wCRCin = 0x00;
	uint8_t wCPoly = 0x31;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 0);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
uint8_t CRC8_MAXIM(uint8_t *data, uint32_t datalen)
{
    uint8_t wCRCin = 0x00;
    uint8_t wCPoly = 0x31;

    InvertUint8(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif

uint16_t crc16(const uint8_t *src, size_t len, uint16_t polynomial,
               uint16_t initial_value, bool pad)
{
    uint16_t crc = initial_value;
    size_t padding = pad ? sizeof(crc) : 0;
    size_t i, b;

    /* src length + padding (if required) */
    for (i = 0; i < len + padding; i++) {
        for (b = 0; b < 8; b++) {
            uint16_t divide = crc & 0x8000UL;

            crc = (crc << 1U);

            /* choose input bytes or implicit trailing zeros */
            if (i < len) {
                crc |= !!(src[i] & (0x80U >> b));
            }

            if (divide != 0U) {
                crc = crc ^ polynomial;
            }
        }
    }

    return crc;
}

uint16_t crc16_ccitt(uint16_t seed, const uint8_t *src, size_t len)
{
    for (; len > 0; len--) {
        uint8_t e, f;

        e = seed ^ *src++;
        f = e ^ (e << 4);
        seed = (seed >> 8) ^ (f << 8) ^ (f << 3) ^ (f >> 4);
    }

    return seed;
}

uint16_t crc16_itu_t(uint16_t seed, const uint8_t *src, size_t len)
{
    for (; len > 0; len--) {
        seed = (seed >> 8U) | (seed << 8U);
        seed ^= *src++;
        seed ^= (seed & 0xffU) >> 4U;
        seed ^= seed << 12U;
        seed ^= (seed & 0xffU) << 5U;
    }

    return seed;
}

/****************************Info********************************************** 
 * Name:    CRC-16/CCITT        x16+x12+x5+1 
 * Width:	16
 * Poly:    0x1021 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Alias:   CRC-CCITT,CRC-16/CCITT-TRUE,CRC-16/KERMIT 
 *****************************************************************************/
#if 0
uint16_t CRC16_CCITT(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0x0000;
	uint16_t wCPoly = 0x1021;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
//这里为了效率，我们不需要将所有Refin和refout为true的输入输出数据移位转换
//只需要将poly二项式转换后，运算时将左移变为右移
uint16_t CRC16_CCITT(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x1021;
    uint8_t wChar = 0;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/CCITT-FALSE   x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0xFFFF 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000 
 * Note: 
 *****************************************************************************/
uint16_t CRC16_CCITT_FALSE(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0xFFFF;
    uint16_t wCPoly = 0x1021;

    while (datalen--) {
        wCRCin ^= *(data++) << 8;
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-16/XMODEM       x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0x0000 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000 
 * Alias:   CRC-16/ZMODEM,CRC-16/ACORN 
 *****************************************************************************/
uint16_t CRC16_XMODEM(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x1021;

    while (datalen--) {
        wCRCin ^= (*(data++) << 8);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-16/X25          x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0XFFFF 
 * Note: 
 *****************************************************************************/
#if 0 
uint16_t CRC16_X25(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0xFFFF;
	uint16_t wCPoly = 0x1021;
	uint8_t wChar = 0;
 
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else
uint16_t CRC16_X25(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0xFFFF;
    uint16_t wCPoly = 0x1021;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin ^ 0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/MODBUS       x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Note: 
 *****************************************************************************/
#if 0 
uint16_t CRC16_MODBUS(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0xFFFF;
	uint16_t wCPoly = 0x8005;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
uint16_t CRC16_MODBUS(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0xFFFF;
    uint16_t wCPoly = 0x8005;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/IBM          x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Alias:   CRC-16,CRC-16/ARC,CRC-16/LHA 
 *****************************************************************************/
#if 0
uint16_t CRC16_IBM(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0x0000;
	uint16_t wCPoly = 0x8005;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
uint16_t CRC16_IBM(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x8005;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/MAXIM        x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Note: 
 *****************************************************************************/
#if 0
uint16_t CRC16_MAXIM(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0x0000;
	uint16_t wCPoly = 0x8005;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else
uint16_t CRC16_MAXIM(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x8005;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin ^ 0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/USB          x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Note: 
 *****************************************************************************/
#if 0
uint16_t CRC16_USB(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0xFFFF;
	uint16_t wCPoly = 0x8005;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else
uint16_t CRC16_USB(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0xFFFF;
    uint16_t wCPoly = 0x8005;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin ^ 0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/DNP          x16+x13+x12+x11+x10+x8+x6+x5+x2+1 
 * Width:	16 
 * Poly:    0x3D65 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Use:     M-Bus,ect. 
 *****************************************************************************/
#if 0
uint16_t CRC16_DNP(uint8_t *data, uint32_t datalen)
{
	uint16_t wCRCin = 0x0000;
	uint16_t wCPoly = 0x3D65;
	uint8_t wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF) ;
}
#else
uint16_t CRC16_DNP(uint8_t *data, uint32_t datalen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x3D65;

    InvertUint16(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = (wCRCin >> 1);
        }
    }
    return (wCRCin ^ 0xFFFF);
}
#endif

uint32_t crc32_ieee(const uint8_t *data, size_t len)
{
    return crc32_ieee_update(0x0, data, len);
}

uint32_t crc32_ieee_update(uint32_t crc, const uint8_t *data, size_t len)
{
    /* crc table generated from polynomial 0xedb88320 */
    static const uint32_t table[16] = {
        0x00000000,
        0x1db71064,
        0x3b6e20c8,
        0x26d930ac,
        0x76dc4190,
        0x6b6b51f4,
        0x4db26158,
        0x5005713c,
        0xedb88320,
        0xf00f9344,
        0xd6d6a3e8,
        0xcb61b38c,
        0x9b64c2b0,
        0x86d3d2d4,
        0xa00ae278,
        0xbdbdf21c,
    };

    crc = ~crc;

    for (size_t i = 0; i < len; i++) {
        uint8_t byte = data[i];

        crc = (crc >> 4) ^ table[(crc ^ byte) & 0x0f];
        crc = (crc >> 4) ^ table[(crc ^ (byte >> 4)) & 0x0f];
    }

    return (~crc);
}

/****************************Info********************************************** 
 * Name:    CRC-32  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 
 * Width:	32 
 * Poly:    0x4C11DB7 
 * Init:    0xFFFFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFFFFF 
 * Alias:   CRC_32/ADCCP 
 * Use:     WinRAR,ect. 
 *****************************************************************************/
#if 0
uint32_t CRC32(uint8_t *data, uint32_t datalen)
{
	uint32_t wCRCin = 0xFFFFFFFF;
	uint32_t wCPoly = 0x04C11DB7;
	uint32_t wChar = 0;
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8((uint8_t *)&wChar,(uint8_t *)&wChar);
		wCRCin ^= (wChar << 24);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80000000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint32(&wCRCin,&wCRCin);
	return (wCRCin ^ 0xFFFFFFFF) ;
}
#else
uint32_t CRC32(uint8_t *data, uint32_t datalen)
{
    uint32_t wCRCin = 0xFFFFFFFF;
    uint32_t wCPoly = 0x04C11DB7;

    InvertUint32(&wCPoly, &wCPoly);
    while (datalen--) {
        wCRCin ^= *(data++);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin ^ 0xFFFFFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-32/MPEG-2  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 
 * Width:	32 
 * Poly:    0x4C11DB7 
 * Init:    0xFFFFFFF 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000000 
 * Note: 
 *****************************************************************************/
uint32_t CRC32_MPEG(uint8_t *data, uint32_t datalen)
{
    uint32_t wCRCin = 0xFFFFFFFF;
    uint32_t wCPoly = 0x04C11DB7;
    uint32_t wChar = 0;
    while (datalen--) {
        wChar = *(data++);
        wCRCin ^= (wChar << 24);
        for (int i = 0; i < 8; i++) {
            if (wCRCin & 0x80000000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin);
}
