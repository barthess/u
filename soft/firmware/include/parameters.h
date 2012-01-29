#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <string.h>

#include <mavlink.h>
#include <common.h>
#include <bart.h>

///**
// * ��������� ���������� ������ ��������� ���� "������" ��� ������ �������.
// */
//typedef struct Mail Mail;
//struct Mail{
//  /**
//   * @brief ��������� �� ������� �����.
//   * @details ����� ����, ��� ������ ������� �������
//   * ��������, ��������� ��������������� � NULL. ��� ����� �������� ���
//   * ������ �������.
//   */
//  void *payload;
//  /**
//   * ���� ����������� �� ���������� ����������, ����� ��������� ��� ������.
//   */
//  msg_t invoice;
//  /**
//   * ��������� �� �������� ����, � ������� ���� �������� �������������
//   * ��������� ����������. �������� ��������� ������ �� �������� ������.
//   * ����� ���� NULL
//   */
//  Mailbox *confirmbox;
//};


typedef struct GlobalStruct_t GlobalStruct_t;
struct GlobalStruct_t
{
  float *value;
  const char **name;
};


void ParametersInit(void);

#endif /* PARAMETERS_H_ */
