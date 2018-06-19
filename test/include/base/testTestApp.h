//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef TESTTESTAPP_H
#define TESTTESTAPP_H

#include "MooseApp.h"

class testTestApp;

template <>
InputParameters validParams<testTestApp>();

class testTestApp : public MooseApp
{
public:
  testTestApp(InputParameters parameters);
  virtual ~testTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};

#endif /* TESTTESTAPP_H */
