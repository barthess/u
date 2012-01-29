#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <string.h>

#include <mavlink.h>
#include <common.h>
#include <bart.h>

///**
// * структура определяет формат сообщений типа "письмо" для обмена данными.
// */
//typedef struct Mail Mail;
//struct Mail{
//  /**
//   * @brief указатель на внешний буфер.
//   * @details После того, как данные забраны берущей
//   * стороной, указатель устанавливается в NULL. Это будет сигналом для
//   * дающей стороны.
//   */
//  void *payload;
//  /**
//   * Поле заполняется по усмотрению приложения, может содержать что угодно.
//   */
//  msg_t invoice;
//  /**
//   * Указатель на почтовый ящик, в который надо прислать подтверждение
//   * успешного выполнения. Аналогия обратного адреса на конверте письма.
//   * Может быть NULL
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
