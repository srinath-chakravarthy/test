//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef COMPUTEDEFGRADBASEDSTRESS_H
#define COMPUTEDEFGRADBASEDSTRESS_H

#include "ComputeStressBase.h"
#include "GuaranteeConsumer.h"

class ComputeDefGradBasedStress;

template <>
InputParameters validParams<ComputeDefGradBasedStress>();

/**
 * ComputeDefGradBasedStress computes stress based on lagrangian strain definition
 **/
class ComputeDefGradBasedStress :  public ComputeStressBase, public GuaranteeConsumer
{
public:
  ComputeDefGradBasedStress(const InputParameters & parameters);
   void initialSetup() override;

protected:
  virtual void initQpStatefulProperties();
  virtual void computeQpStress();

  const MaterialProperty<RankTwoTensor> & _deformation_gradient;
  /*
  const MaterialProperty<RankFourTensor> & _elasticity_tensor;

  MaterialProperty<RankTwoTensor> & _stress;
  MaterialProperty<RankFourTensor> & _Jacobian_mult;
   */
};

#endif
