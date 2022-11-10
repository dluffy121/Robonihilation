# Robonihilation (Unreal Engine 5)(C++)

An Unreal Engine third-person shooter game, where the player is deployed on an arctic research station to annihilate the robots gone rogue. Various features of Unreal Engine in the form of C++ and blueprint system was utilized to make character movements, animations, combat, health system, AI, etc.

## Hightlights
1. Character Movement
   Handling input by overriding ACharacter::SetupPlayerInputComponent and binding actions and axes to perform intended behaviour
   Leveraging Animation blueprint's Eventgraphs and AnimGraph to make use of blend space animations for aiming and locomotion
   
2. Character Combat
   Shooting, Sockets, Particle System, Bone Hiding
   
3. Character AI
   Nav Mesh
    2.  LineOfSight
    3.  Focusing (SetFocus)
    4.  Chase (MoveToActor)
    5.  Blackboard
    6.  Behavior Trees
         1.  Selector
         2.  Sequence
         3.  Tasks
         4.  Decorators
         5.  Services

4. Sound
   SpawnSoundAttached, SoundCue, Spacialization
   
5. Widget
   Updating from code as per conditions

## Summary
1. Character setup
   1. Movement Control
   2. Input based Implementation
   3. Aiming
   4. Syncing Animation and movement params
2. Animation Blueprint
   1. Animation State machines
   2. Blend Space
3. Gun Setup
4. Dynamic Actor Spawning
5. Mesh Sockets and Attaching
6. Mesh Bone Hiding
7. Particle System Spawning
   1. UGameplayStatics::SpawnEmitterAtLocation
   2. UGameplayStatics::SpawnEmitterAttached
8. Blueprint Pure
9. Methods:
   1. PlayerController::GetPlayerViewpoint
   2. PlayerController::GameHasEnded
   3. ACharacter::DetachFromControllerPendingDestroy
   4. USkinnedMeshComponent::HideBoneByName
   5. TActorRange<>
   6. Controller::IsPlayerController
   7. Controller::GameHasEnded
   8. USceneComponent::GetSocketLocation
10. Vector Mathematics:
    1. Inverse Transform Vector
    2. Inverse Transform Direction

## Dependencies
1. Shooter Asset Pack: available only via course link
   > Not all links may be available==
