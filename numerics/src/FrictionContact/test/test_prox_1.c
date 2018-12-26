/* Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 *
 * Copyright 2016 INRIA.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
char *** test_collection(int, char **);

char *** test_collection(int n_data_1, char ** data_collection)
{
  int n_test=150;
  int n_entry = 50;
  char *** test_prox = (char ***)malloc(n_test*sizeof(char **));

  for (int n =0 ; n <n_test ; n++)
  {
    test_prox[n] = (char **)malloc(n_entry*sizeof(char *));
  }

  int n =0;
  int e=0;
  
  int d=0;/* "./data/FC3D_Example1_SBM.dat"; */
  e=0;
  test_prox[n][e++] = data_collection[d];
  test_prox[n][e++] = "0";
  test_prox[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_prox[n][e++], "%d", SICONOS_FRICTION_3D_PROX);
  test_prox[n][e++] = "1e-08";
  test_prox[n][e++] = "100";
  test_prox[n][e++] = "---";
  n++;

  d=9;
  e=0;
  test_prox[n][e++] = data_collection[d];
  test_prox[n][e++] = "0";
  test_prox[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_prox[n][e++], "%d", SICONOS_FRICTION_3D_PROX);
  test_prox[n][e++] = "1e-08";
  test_prox[n][e++] = "1000000";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "dparam";
  test_prox[n][e++] = "3";
  test_prox[n][e++] = "1e4";
  test_prox[n][e++] = "iparam";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "---";
  n++;

  e=0;
  test_prox[n][e++] = data_collection[d];
  test_prox[n][e++] = "0";
  test_prox[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_prox[n][e++], "%d", SICONOS_FRICTION_3D_PROX);
  test_prox[n][e++] = "1e-08";
  test_prox[n][e++] = "1000000";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "dparam";
  test_prox[n][e++] = "3";
  test_prox[n][e++] = "1e4";
  test_prox[n][e++] = "iparam";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "---";
  n++;
  
  d=6;
  e=0;
  test_prox[n][e++] = data_collection[d];
  test_prox[n][e++] = "0";
  test_prox[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_prox[n][e++], "%d", SICONOS_FRICTION_3D_PROX);
  test_prox[n][e++] = "1e-08";
  test_prox[n][e++] = "1000000";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "0";
  test_prox[n][e++] = "dparam";
  test_prox[n][e++] = "3";
  test_prox[n][e++] = "1e4";
  test_prox[n][e++] = "iparam";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "1";
  test_prox[n][e++] = "---";
  n++;

 

  test_prox[n][0] ="---";
  return test_prox;

}
