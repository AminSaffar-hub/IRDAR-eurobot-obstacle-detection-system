/*
 * INTERRUPT.h
 *
 * Created: 12/21/2018 8:42:43 PM
 *  Author: Amin Saffar
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_


void init_PCInt();
void enable_PCI_interrupts(int i);
void disable_PCI_interrupts();


#endif