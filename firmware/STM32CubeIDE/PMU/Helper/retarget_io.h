/*
 * retarget_io.h
 *
 *  Created on: 7 жовт. 2020 р.
 *      Author: timohin
 */

#ifndef RETARGET_IO_H_
#define RETARGET_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

int32_t __io_putchar (int32_t ch);
int32_t __io_getchar (void);

#ifdef __cplusplus
}
#endif

#endif /* RETARGET_IO_H_ */
