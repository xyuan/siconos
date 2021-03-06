// generated with build_from_doxygen.py
#ifndef SiconosFullKernelGenerated_hpp
#define SiconosFullKernelGenerated_hpp
#include <SiconosConfig.h>
#ifdef WITH_SERIALIZATION
#include "SiconosKernel.hpp"
SICONOS_IO_REGISTER(SiconosException,
  (_reportMsg))
SICONOS_IO_REGISTER(SiconosMemory,
  (_indx)
  (_nbVectorsInMemory))
SICONOS_IO_REGISTER(BlockVector,
  (_sizeV)
  (_tabIndex)
  (_vect))
SICONOS_IO_REGISTER_WITH_BASES(BlockMatrix,(SiconosMatrix),
  (_dimCol)
  (_dimRow)
  (_mat)
  (_tabCol)
  (_tabRow))
SICONOS_IO_REGISTER(SiconosMatrix,
  (_num))
SICONOS_IO_REGISTER(GraphProperties,
  (symmetric))
SICONOS_IO_REGISTER(DynamicalSystemProperties,
  (W)
  (WBoundaryConditions)
  (absolute_position)
  (lower_block)
  (osi)
  (upper_block)
  (workMatrices)
  (workVectors))
SICONOS_IO_REGISTER(InteractionProperties,
  (absolute_position)
  (absolute_position_proj)
  (block)
  (forControl)
  (source)
  (source_pos)
  (target)
  (target_pos)
  (workBlockVectors)
  (workMatrices)
  (workVectors))
SICONOS_IO_REGISTER(MatrixIntegrator,
  (_DS)
  (_E)
  (_OSI)
  (_TD)
  (_isConst)
  (_mat)
  (_nsds)
  (_plugin)
  (_sim))
SICONOS_IO_REGISTER_WITH_BASES(DynamicalSystemsGraph,(_DynamicalSystemsGraph),
  (Ad)
  (AdInt)
  (B)
  (Bd)
  (L)
  (Ld)
  (dummy)
  (e)
  (groupId)
  (jacgx)
  (name)
  (pluginB)
  (pluginJacgx)
  (pluginL)
  (pluginU)
  (tmpXdot)
  (u))
SICONOS_IO_REGISTER_WITH_BASES(InteractionsGraph,(_InteractionsGraph),
  (blockProj)
  (dummy)
  (lower_blockProj)
  (name)
  (upper_blockProj))
SICONOS_IO_REGISTER(Topology,
  (_DSG)
  (_IG)
  (_hasChanged)
  (_numberOfConstraints)
  (_symmetric))
SICONOS_IO_REGISTER_WITH_BASES(MultipleImpactNSL,(NonSmoothLaw),
  (_ElasCof)
  (_ResCof)
  (_Stiff))
SICONOS_IO_REGISTER_WITH_BASES(ComplementarityConditionNSL,(NonSmoothLaw),
)
SICONOS_IO_REGISTER_WITH_BASES(FixedBC,(BoundaryCondition),
)
SICONOS_IO_REGISTER_WITH_BASES(HarmonicBC,(BoundaryCondition),
  (_a)
  (_aV)
  (_b)
  (_bV)
  (_omega)
  (_omegaV)
  (_phi)
  (_phiV))
SICONOS_IO_REGISTER(NSLawMatrix,
)
SICONOS_IO_REGISTER_WITH_BASES(EqualityConditionNSL,(NonSmoothLaw),
)
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactFrictionNSL,(NonSmoothLaw),
  (_en)
  (_et)
  (_mu))
SICONOS_IO_REGISTER_WITH_BASES(MixedComplementarityConditionNSL,(NonSmoothLaw),
  (_equalitySize))
SICONOS_IO_REGISTER(PluggedObject,
  (_pluginName))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEuler3DR,(NewtonEuler1DR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearTIR,(FirstOrderR),
  (_e))
SICONOS_IO_REGISTER(NonSmoothDynamicalSystem,
  (_BVP)
  (_T)
  (_author)
  (_changeLog)
  (_date)
  (_description)
  (_mIsLinear)
  (_t)
  (_t0)
  (_title)
  (_topology))
SICONOS_IO_REGISTER(BoundaryCondition,
  (_pluginPrescribedVelocity)
  (_prescribedVelocity)
  (_prescribedVelocityOld)
  (_velocityIndices))
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactNSL,(NonSmoothLaw),
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEuler1DR,(NewtonEulerR),
  (_AUX1)
  (_AUX2)
  (_NPG1)
  (_NPG2)
  (_Nc)
  (_Pc1)
  (_Pc2)
  (_RotationAbsToContactFrame)
  (_isOnContact)
  (_relNc)
  (_relPc1)
  (_relPc2)
  (_rotationMatrixAbsToBody))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIR,(LagrangianR),
  (_F)
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(NormalConeNSL,(NonSmoothLaw),
  (_H)
  (_K))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerR,(Relation),
  (_T)
  (_contactForce)
  (_dotjachq)
  (_e)
  (_jacglambda)
  (_jachlambda)
  (_jachq)
  (_jachqDot)
  (_jachqT)
  (_plugindotjacqh)
  (_secondOrderTimeDerivativeTerms))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianCompliantLinearTIR,(LagrangianR),
  (_F)
  (_e))
SICONOS_IO_REGISTER(NonSmoothDynamicalSystem::Change,
  (ds)
  (i)
  (typeOfChange))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearR,(FirstOrderR),
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearTIDS,(FirstOrderLinearDS),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderType2R,(FirstOrderR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderType1R,(FirstOrderR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearDS,(FirstOrderNonLinearDS),
  (_A)
  (_b)
  (_hasConstantA)
  (_hasConstantB)
  (_pluginA)
  (_pluginb))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianCompliantR,(LagrangianR),
  (_pluginJachlambda))
SICONOS_IO_REGISTER(NonSmoothLaw,
  (_size))
SICONOS_IO_REGISTER_WITH_BASES(RelayNSL,(NonSmoothLaw),
  (_lb)
  (_ub))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderR,(Relation),
  (_B)
  (_C)
  (_D)
  (_F)
  (_K)
SICONOS_IO_REGISTER(Relation,
  (_pluginJacglambda)
  (_pluginJacgx)
  (_pluginJachlambda)
  (_pluginJachx)
  (_pluginJachz)
  (_plugine)
  (_pluginf)
  (_pluging)
  (_pluginh)
  (_relationType)
  (_subType))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianRheonomousR,(LagrangianR),
  (_hDot)
  (_pluginhDot))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderNonLinearR,(FirstOrderR),
)
SICONOS_IO_REGISTER(Interaction,
  (__count)
  (_has2Bodies)
  (_interactionSize)
  (_lambda)
  (_lambdaMemory)
  (_lambdaOld)
  (_linkToDSVariables)
  (_lowerLevelForInput)
  (_lowerLevelForOutput)
  (_nslaw)
  (_number)
  (_relation)
  (_relationMatrices)
  (_relationVectors)
  (_sizeOfDS)
  (_upperLevelForInput)
  (_upperLevelForOutput)
  (_y)
  (_yMemory)
  (_yOld)
  (_y_k))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianR,(Relation),
  (_dotjachq)
  (_jachlambda)
  (_jachq)
  (_jachqDot)
  (_pluginJachq))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearDiagonalDS,(LagrangianDS),
  (_damping)
  (_mu)
  (_stiffness))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderNonLinearDS,(DynamicalSystem),
  (_M)
  (_f)
  (_fold)
  (_invM)
  (_jacobianfx)
  (_pluginJacxf)
  (_pluginM)
  (_pluginf)
  (_rMemory))
SICONOS_IO_REGISTER(DynamicalSystem,
  (__count)
  (_jacxRhs)
  (_n)
  (_number)
  (_r)
  (_stepsInMemory)
  (_x)
  (_x0)
  (_xMemory)
  (_z))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianScleronomousR,(LagrangianR),
  (_dotjacqhXqdot)
  (_plugindotjacqh))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIDS,(LagrangianDS),
  (_C)
  (_K))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianDS,(DynamicalSystem),
  (_boundaryConditions)
  (_fExt)
  (_fGyr)
  (_fInt)
  (_forces)
  (_forcesMemory)
  (_hasConstantFExt)
  (_hasConstantMass)
  (_inverseMass)
  (_jacobianFGyrq)
  (_jacobianFGyrqDot)
  (_jacobianFIntq)
  (_jacobianFIntqDot)
  (_jacobianqDotForces)
  (_jacobianqForces)
  (_mass)
  (_ndof)
  (_p)
  (_pMemory)
  (_pluginFExt)
  (_pluginFGyr)
  (_pluginFInt)
  (_pluginJacqDotFGyr)
  (_pluginJacqDotFInt)
  (_pluginJacqFGyr)
  (_pluginJacqFInt)
  (_pluginMass)
  (_q)
  (_q0)
  (_qMemory)
  (_reactionToBoundaryConditions)
  (_rhsMatrices)
  (_velocity0)
  (_velocityMemory))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerDS,(DynamicalSystem),
  (_I)
  (_T)
  (_Tdot)
  (_acceleration)
  (_boundaryConditions)
  (_computeJacobianFIntqByFD)
  (_computeJacobianFInttwistByFD)
  (_computeJacobianMIntqByFD)
  (_computeJacobianMInttwistByFD)
  (_dotq)
  (_dotqMemory)
  (_epsilonFD)
  (_fExt)
  (_fInt)
  (_forcesMemory)
  (_hasConstantFExt)
  (_hasConstantMExt)
  (_inverseMass)
  (_isMextExpressedInInertialFrame)
  (_jacobianFIntq)
  (_jacobianFInttwist)
  (_jacobianMExtq)
  (_jacobianMGyrtwist)
  (_jacobianMIntq)
  (_jacobianMInttwist)
  (_jacobianWrenchTwist)
  (_jacobianWrenchq)
  (_mExt)
  (_mGyr)
  (_mInt)
  (_massMatrix)
  (_ndof)
  (_nullifyMGyr)
  (_p)
  (_pluginFExt)
  (_pluginFInt)
  (_pluginJacqFInt)
  (_pluginJacqMInt)
  (_pluginJactwistFInt)
  (_pluginJactwistMInt)
  (_pluginMExt)
  (_pluginMInt)
  (_q)
  (_q0)
  (_qDim)
  (_qMemory)
  (_reactionToBoundaryConditions)
  (_rhsMatrices)
  (_scalarMass)
  (_twist)
  (_twist0)
  (_twistMemory)
  (_wrench))
SICONOS_IO_REGISTER(ExtraAdditionalTerms,
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanBilbaoOSI,(OneStepIntegrator),
)
SICONOS_IO_REGISTER(InteractionManager,
  (_nslaws))
SICONOS_IO_REGISTER_WITH_BASES(TimeDiscretisationEvent,(Event),
)
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingCombinedProjection,(TimeStepping),
  (_constraintTol)
  (_constraintTolUnilateral)
  (_cumulatedNewtonNbIterations)
  (_doCombinedProj)
  (_doCombinedProjOnEquality)
  (_indexSetLevelForProjection)
  (_isIndexSetsStable)
  (_kIndexSetMax)
  (_maxViolationEquality)
  (_maxViolationUnilateral)
  (_nbCumulatedProjectionIteration)
  (_nbIndexSetsIteration)
  (_nbProjectionIteration)
  (_projectionMaxIteration))
SICONOS_IO_REGISTER_WITH_BASES(EventDriven,(Simulation),
  (_DSG0)
  (_TOL_ED)
  (_indexSet0)
  (_isNewtonConverge)
  (_istate)
  (_localizeEventMaxIter)
  (_newtonMaxIteration)
  (_newtonNbIterations)
  (_newtonResiduDSMax)
  (_newtonResiduYMax)
  (_newtonTolerance)
  (_numberOfOneStepNSproblems))
SICONOS_IO_REGISTER_WITH_BASES(OSNSMultipleImpact,(LinearOSNS),
  (_DataMatrix)
  (_IsImpactEnd)
  (_Kcontact)
  (_Tol_Ener)
  (_Tol_Vel)
  (_WorkcContact)
  (_ZeroEner_EndIm)
  (_ZeroVel_EndIm)
  (_deltaImpulseContact)
  (_deltaP)
  (_distributionVector)
  (_elasticyCoefficientcontact)
  (_energyContact)
  (_energyPrimaryContact)
  (_forceContact)
  (_impulseContactUpdate)
  (_impulseVariable)
  (_isPrimaryContactEnergy)
  (_nContact)
  (_nStepMax)
  (_nStepSave)
  (_namefile)
  (_oldVelocityContact)
  (_primaryContactId)
  (_relativeVelocityPrimaryContact)
  (_restitutionContact)
  (_saveData)
  (_sizeDataSave)
  (_stateContact)
  (_stepMaxSave)
  (_stepMinSave)
  (_timeVariable)
  (_tolImpact)
  (_tolImpulseContact)
  (_typeCompLaw)
  (_velocityContact))
SICONOS_IO_REGISTER_WITH_BASES(NonSmoothEvent,(Event),
)
SICONOS_IO_REGISTER_WITH_BASES(QP,(OneStepNSProblem),
  (_Q)
  (_p))
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingD1Minus,(Simulation),
)
SICONOS_IO_REGISTER_WITH_BASES(MLCPProjectOnConstraints,(MLCP),
  (_alpha)
  (_doProjOnEquality)
  (_useMassNormalization))
SICONOS_IO_REGISTER_WITH_BASES(NewMarkAlphaOSI,(OneStepIntegrator),
  (_IsVelocityLevel)
  (_alpha_f)
  (_alpha_m)
  (_beta)
  (_gamma)
  (_orderDenseOutput))
SICONOS_IO_REGISTER_WITH_BASES(AVI,(LinearOSNS),
)
SICONOS_IO_REGISTER(Simulation,
  (_OSIDSmap)
  (_T)
  (_allNSProblems)
  (_allOSI)
  (_eventsManager)
  (_interman)
  (_isInitialized)
  (_name)
  (_nsds)
  (_nsdsChangeLogPosition)
  (_numberOfIndexSets)
  (_printStat)
  (_relativeConvergenceCriterionHeld)
  (_relativeConvergenceTol)
  (_staticLevels)
  (_tend)
  (_tinit)
  (_tolerance)
  (_tout)
  (_useRelativeConvergenceCriterion)
  (statOut))
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingDirectProjection,(TimeStepping),
  (_constraintTol)
  (_constraintTolUnilateral)
  (_doOnlyProj)
  (_doProj)
  (_indexSetLevelForProjection)
  (_maxViolationEquality)
  (_maxViolationUnilateral)
  (_nbProjectionIteration)
  (_projectionMaxIteration))
SICONOS_IO_REGISTER_WITH_BASES(LinearOSNS,(OneStepNSProblem),
  (_M)
  (_keepLambdaAndYState)
  (_q)
  (_w)
  (_z))
SICONOS_IO_REGISTER_WITH_BASES(ZeroOrderHoldOSI,(OneStepIntegrator),
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(Equality,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(GenericMechanical,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanCombinedProjectionOSI,(MoreauJeanOSI),
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanDirectProjectionOSI,(MoreauJeanOSI),
  (_activateYPosThreshold)
  (_activateYVelThreshold)
  (_deactivateYPosThreshold)
  (_deactivateYVelThreshold))
SICONOS_IO_REGISTER_WITH_BASES(TimeStepping,(Simulation),
  (_computeResiduR)
  (_computeResiduY)
  (_displayNewtonConvergence)
  (_isNewtonConverge)
  (_newtonCumulativeNbIterations)
  (_newtonMaxIteration)
  (_newtonNbIterations)
  (_newtonOptions)
  (_newtonResiduDSMax)
  (_newtonResiduRMax)
  (_newtonResiduYMax)
  (_newtonTolerance)
  (_newtonUpdateInteractionsPerIteration)
  (_resetAllLambda)
  (_warnOnNonConvergence))
SICONOS_IO_REGISTER(OneStepIntegrator,
  (_dynamicalSystemsGraph)
  (_explicitJacobiansOfRelation)
  (_extraAdditionalTerms)
  (_integratorType)
  (_isInitialized)
  (_levelMaxForInput)
  (_levelMaxForOutput)
  (_levelMinForInput)
  (_levelMinForOutput)
  (_simulation)
  (_sizeMem)
  (_steps))
SICONOS_IO_REGISTER_WITH_BASES(Relay,(LinearOSNS),
  (_lb)
  (_ub))
SICONOS_IO_REGISTER_WITH_BASES(LCP,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(MLCP,(LinearOSNS),
  (_curBlock)
  (_m)
  (_n))
SICONOS_IO_REGISTER_WITH_BASES(SchatzmanPaoliOSI,(OneStepIntegrator),
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER(Event,
  (_dTime)
  (_eventCreated)
  (_k)
  (_reschedule)
  (_td)
  (_tick)
  (_tickIncrement)
  (_timeOfEvent)
  (_type))
SICONOS_IO_REGISTER(TimeDiscretisation,
  (_h)
  (_hgmp)
  (_t0)
  (_t0gmp)
  (_tk)
  (_tkV)
  (_tkp1))
SICONOS_IO_REGISTER(EventsManager,
  (_GapLimit2Events)
  (_NSeventInsteadOfTD)
  (_T)
  (_eNonSmooth)
  (_events)
  (_k)
  (_td))
SICONOS_IO_REGISTER(OneStepNSProblem,
  (_hasBeenUpdated)
  (_indexSetLevel)
  (_inputOutputLevel)
  (_maxSize)
  (_simulation)
  (_sizeOutput))
SICONOS_IO_REGISTER(OSNSMatrix,
  (_M1)
  (_M2)
  (_dimColumn)
  (_dimRow)
  (_storageType))
SICONOS_IO_REGISTER_WITH_BASES(OSNSMatrixProjectOnConstraints,(OSNSMatrix),
)
SICONOS_IO_REGISTER(BlockCSRMatrix,
  (_diagsize0)
  (_diagsize1)
  (_nc)
  (_nr)
  (_sparseBlockStructuredMatrix)
  (colPos)
  (rowPos))
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanGOSI,(OneStepIntegrator),
  (_WBoundaryConditionsMap)
  (_explicitNewtonEulerDSOperators)
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanOSI,(OneStepIntegrator),
  (_explicitNewtonEulerDSOperators)
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(EulerMoreauOSI,(OneStepIntegrator),
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))

template <class Archive>
void siconos_io_register_generated_Kernel(Archive& ar)
{
  ar.register_type(static_cast<SiconosException*>(nullptr));
  ar.register_type(static_cast<SiconosMemory*>(nullptr));
  ar.register_type(static_cast<BlockVector*>(nullptr));
  ar.register_type(static_cast<BlockMatrix*>(nullptr));
  ar.register_type(static_cast<GraphProperties*>(nullptr));
  ar.register_type(static_cast<DynamicalSystemProperties*>(nullptr));
  ar.register_type(static_cast<InteractionProperties*>(nullptr));
  ar.register_type(static_cast<MatrixIntegrator*>(nullptr));
  ar.register_type(static_cast<DynamicalSystemsGraph*>(nullptr));
  ar.register_type(static_cast<InteractionsGraph*>(nullptr));
  ar.register_type(static_cast<Topology*>(nullptr));
  ar.register_type(static_cast<MultipleImpactNSL*>(nullptr));
  ar.register_type(static_cast<ComplementarityConditionNSL*>(nullptr));
  ar.register_type(static_cast<FixedBC*>(nullptr));
  ar.register_type(static_cast<HarmonicBC*>(nullptr));
  ar.register_type(static_cast<NSLawMatrix*>(nullptr));
  ar.register_type(static_cast<EqualityConditionNSL*>(nullptr));
  ar.register_type(static_cast<NewtonImpactFrictionNSL*>(nullptr));
  ar.register_type(static_cast<MixedComplementarityConditionNSL*>(nullptr));
  ar.register_type(static_cast<PluggedObject*>(nullptr));
  ar.register_type(static_cast<NewtonEuler3DR*>(nullptr));
  ar.register_type(static_cast<FirstOrderLinearTIR*>(nullptr));
  ar.register_type(static_cast<NonSmoothDynamicalSystem*>(nullptr));
  ar.register_type(static_cast<BoundaryCondition*>(nullptr));
  ar.register_type(static_cast<NewtonImpactNSL*>(nullptr));
  ar.register_type(static_cast<NewtonEuler1DR*>(nullptr));
  ar.register_type(static_cast<LagrangianLinearTIR*>(nullptr));
  ar.register_type(static_cast<NormalConeNSL*>(nullptr));
  ar.register_type(static_cast<NewtonEulerR*>(nullptr));
  ar.register_type(static_cast<LagrangianCompliantLinearTIR*>(nullptr));
  ar.register_type(static_cast<NonSmoothDynamicalSystem::Change*>(nullptr));
  ar.register_type(static_cast<FirstOrderLinearR*>(nullptr));
  ar.register_type(static_cast<FirstOrderLinearTIDS*>(nullptr));
  ar.register_type(static_cast<FirstOrderType2R*>(nullptr));
  ar.register_type(static_cast<FirstOrderType1R*>(nullptr));
  ar.register_type(static_cast<FirstOrderLinearDS*>(nullptr));
  ar.register_type(static_cast<LagrangianCompliantR*>(nullptr));
  ar.register_type(static_cast<RelayNSL*>(nullptr));
  ar.register_type(static_cast<LagrangianRheonomousR*>(nullptr));
  ar.register_type(static_cast<FirstOrderNonLinearR*>(nullptr));
  ar.register_type(static_cast<Interaction*>(nullptr));
  ar.register_type(static_cast<LagrangianLinearDiagonalDS*>(nullptr));
  ar.register_type(static_cast<FirstOrderNonLinearDS*>(nullptr));
  ar.register_type(static_cast<LagrangianScleronomousR*>(nullptr));
  ar.register_type(static_cast<LagrangianLinearTIDS*>(nullptr));
  ar.register_type(static_cast<LagrangianDS*>(nullptr));
  ar.register_type(static_cast<NewtonEulerDS*>(nullptr));
  ar.register_type(static_cast<MoreauJeanBilbaoOSI*>(nullptr));
  ar.register_type(static_cast<InteractionManager*>(nullptr));
  ar.register_type(static_cast<TimeDiscretisationEvent*>(nullptr));
  ar.register_type(static_cast<TimeSteppingCombinedProjection*>(nullptr));
  ar.register_type(static_cast<EventDriven*>(nullptr));
  ar.register_type(static_cast<OSNSMultipleImpact*>(nullptr));
  ar.register_type(static_cast<NonSmoothEvent*>(nullptr));
  ar.register_type(static_cast<QP*>(nullptr));
  ar.register_type(static_cast<TimeSteppingD1Minus*>(nullptr));
  ar.register_type(static_cast<MLCPProjectOnConstraints*>(nullptr));
  ar.register_type(static_cast<NewMarkAlphaOSI*>(nullptr));
  ar.register_type(static_cast<AVI*>(nullptr));
  ar.register_type(static_cast<TimeSteppingDirectProjection*>(nullptr));
  ar.register_type(static_cast<ZeroOrderHoldOSI*>(nullptr));
  ar.register_type(static_cast<Equality*>(nullptr));
  ar.register_type(static_cast<GenericMechanical*>(nullptr));
  ar.register_type(static_cast<MoreauJeanCombinedProjectionOSI*>(nullptr));
  ar.register_type(static_cast<MoreauJeanDirectProjectionOSI*>(nullptr));
  ar.register_type(static_cast<TimeStepping*>(nullptr));
  ar.register_type(static_cast<Relay*>(nullptr));
  ar.register_type(static_cast<LCP*>(nullptr));
  ar.register_type(static_cast<MLCP*>(nullptr));
  ar.register_type(static_cast<SchatzmanPaoliOSI*>(nullptr));
  ar.register_type(static_cast<TimeDiscretisation*>(nullptr));
  ar.register_type(static_cast<EventsManager*>(nullptr));
  ar.register_type(static_cast<OSNSMatrix*>(nullptr));
  ar.register_type(static_cast<OSNSMatrixProjectOnConstraints*>(nullptr));
  ar.register_type(static_cast<BlockCSRMatrix*>(nullptr));
  ar.register_type(static_cast<MoreauJeanGOSI*>(nullptr));
  ar.register_type(static_cast<MoreauJeanOSI*>(nullptr));
  ar.register_type(static_cast<EulerMoreauOSI*>(nullptr));
}
#endif
#endif
