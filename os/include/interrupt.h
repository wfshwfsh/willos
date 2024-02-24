/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  定义 PIT(周期中断定时器) 相关函数
 *
 *        Version:  1.0
 *        Created:  2013年11月16日 11时26分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_INTERRUPT_H_
#define INCLUDE_INTERRUPT_H_

#include "types.h"

void init_int8295a();
void int8295a_send_eoi(int nr);

#endif 	// INCLUDE_INTERRUPT_H_
