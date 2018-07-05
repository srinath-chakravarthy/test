/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComputeNeoHokkeanBasedStress.h
 * Author: srinath
 *
 * Created on July 5, 2018, 3:09 PM
 */

#ifndef COMPUTENEOHOKKEANBASEDSTRESS_H
#define COMPUTENEOHOKKEANBASEDSTRESS_H

#include "ComputeDefGradBasedStress.h"

class ComputeNeoHookeanBasedStress : public ComputeDefGradBasedStress
{
public:
    ComputeNeoHookeanBasedStress(const InputParameters & parameters);

private:
    virtual void computeQpStress() override;

};

#endif /* COMPUTENEOHOKKEANBASEDSTRESS_H */

