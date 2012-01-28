#ifndef PARAMETERS_H_
#define PARAMETERS_H_

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


int32_t key_value_search(char* key);
void set_global_mavlink_value(mavlink_param_set_t *set);

#endif /* PARAMETERS_H_ */
