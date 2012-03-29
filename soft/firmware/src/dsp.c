#include "ch.h"
#include "dsp.h"


/** �������� ���� � ������������ ���������� */
uint32_t pack8to32(uint8_t *buf){
  uint32_t result = 0;
  result |= buf[0]<<24;
  result |= buf[1]<<16;
  result |= buf[2]<<8;
  result |= buf[3];
  return result;
}
uint16_t pack8to16(uint8_t *buf){
  uint16_t result = 0;
  result |= buf[0]<<8;
  result |= buf[1];
  return result;
}


/* �������� ������� ��������.
 * ��� ����� ����������� ������ 1
 * �������� ������ ���� ������������� �� ������ �������
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 */
int32_t Simpson(int32_t a, int32_t b, int32_t c, int32_t t){
  return (t * (a + 4*b + c)) / 3;
}

/* �������� ������� �������� 3/8.
 * ��� ����� ����������� ������ 1
 * �������� ������ ���� ������������� �� ������ �������
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 *
 * �� ������� �� 8 ����� ���������, ���� � ���������� ������� ������������
 * ��������� �� ������� ������, �� ������ ���������� ������������ � �����������.
 */
int32_t Simpson38(int32_t a, int32_t b, int32_t c, int32_t d, int32_t t){
  return (t * 3 * (a + 3*b + 3*c + d)) / 8;
}


/* ������� �� ��������������� ���� � �������� ����� ��� */
int16_t complement2signed(uint8_t msb, uint8_t lsb){
  uint16_t word = 0;
  word = (msb << 8) + lsb;
  if (msb > 0x7F){
    return -1 * ((int16_t)((~word) + 1));
  }
  return (int16_t)word;
}
