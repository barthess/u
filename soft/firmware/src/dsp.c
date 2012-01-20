#include "ch.h"
#include "dsp.h"


/** �������� ���� � ������������ ���������� */
int32_t pack8to32(uint8_t *buf){
  return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + (buf[3]);
}
int16_t pack8to16(uint8_t *buf){
  return (buf[0]<<8) + buf[1];
}
uint32_t upack8to32(uint8_t *buf){
  return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + (buf[3]);
}
uint16_t upack8to16(uint8_t *buf){
  return (buf[0]<<8) + buf[1];
}


/* �������� ������� ��������.
 * ��� ����� ����������� ������ 1
 * �������� ������ ���� ������������� �� ������ �������
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 */
uint32_t Simpson(uint32_t a, uint32_t b, uint32_t c){
  return ((a + 4*b + c) / 3);
}

/* �������� ������� �������� 3/8.
 * ��� ����� ����������� ������ 1
 * �������� ������ ���� ������������� �� ������ �������
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 *
 * �� ������� �� 8 ����� ���������, ���� � ���������� ������� ������������
 * ��������� �� ������� ������, �� ������ ���������� ������������ � �����������.
 */
uint32_t Simpson38(uint32_t a, uint32_t b, uint32_t c, uint32_t d){
  return ((3 * (a + 3*b + 3*c + d)) / 8);
}


/* ������� �� ��������������� ���� */
int16_t complement2signed(uint8_t msb, uint8_t lsb){
  uint16_t word = 0;
  word = (msb << 8) + lsb;
  if (msb > 0x7F){
    return -1 * ((int16_t)((~word) + 1));
  }
  return (int16_t)word;
}
