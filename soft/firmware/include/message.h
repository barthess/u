#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <mavlink.h>
#include <common.h>


/**
 * Structure for data exchange with confimation capability.
 */
typedef struct Mail Mail;
struct Mail{
  /**
   * @brief   pointer to external buffer.
   * @details When receiver got data it must be set this pointer to NULL
   *          as a ready flag.
   */
  void *payload;
  /**
   * Content is on program responsibility. Can be contain anything.
   */
  msg_t invoice;
  /**
   * Protection semaphore.
   * Set to NULL if unused.
   */
  BinarySemaphore *sem;
};


void MsgInit(void);
void MavInit(void);


#endif /* MESSAGE_H_ */

