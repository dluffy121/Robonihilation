# Robonihilation (Unreal Engine 5)(C++)

An Unreal Engine third-person shooter game, where the player is deployed on an arctic research station to annihilate the robots gone rogue. Various features of Unreal Engine in the form of C++ and blueprint system was utilized to make character movements, animations, combat, health system, AI, etc.

## Hightlights

### Character Movement

   Input is handled by overriding **ACharacter::SetupPlayerInputComponent** and binding actions and axes to perform intended behaviour.<br>
   Leveraging Animation blueprint's **Eventgraph** and **AnimGraph** to make use of blend space animations for aiming and locomotion.<br>
   Different character states like grounded, airborne, jumping, etc are defined and linked with each other using transitions to from **animation state machines**.
   Transitions happen between these states depending on conditions and animations are played accordingly.
   
   ![LocomotionStateMachine](https://user-images.githubusercontent.com/43366313/201526752-b41ae8c7-6e3e-42b8-8cfe-4aee4b8ae3e7.png)<br>*Locomotion State Machine*
   
   **Blend spaces** are used to blend between multiple animations depending upon some parameters like Locomotion blend space helps with leg movement done in different directions.<br>
   
   ![Locomotion](https://user-images.githubusercontent.com/43366313/201526912-f7911a55-5d90-4215-892c-8e9665aff4a9.gif)<br>*Locomotion Animation*
   
   Aiming movement is achieved by implementing **APawn::AddControllerPitchInput** and **APawn::AddControllerYawInput**
   
   ![Aiming](https://user-images.githubusercontent.com/43366313/201527273-ff1c4297-6e80-4718-b215-9fd90137a25a.gif)<br>*Aiming*
   
   Along with these basic movement ability to walk is also implemented.
   
   ![Walking](https://user-images.githubusercontent.com/43366313/201527353-0ff44dfb-a754-4aa0-a11d-23f4cbbd4ab6.gif)<br>*Walking*

### Character Combat

   Combat happens in the form of shooting fake bullets, which follow the ray trace from gun to the forward direction of the player camera.
   Unreal Engine's damage system is utilized to inflict damage to player or enemy pawns, **APawn::TakeDamage** method is overriden to achieve this and is called on the pawn when bullet hits.
   
   ![Shooting](https://user-images.githubusercontent.com/43366313/201525881-bb52a4e4-9c8d-4e94-a8ef-b854735c7008.gif)<br>*Shooting*
   
   Paticles are triggered from gun muzzle when bullet is fired and also when the bullet hits a surface. Different particles are triggered when hitting pawns.
   Spawning of particles happens with the help of **UWorld::SpawnEmitterAtLocation** and **UWorld::SpawnEmitterAttached**
   
   ![Shooting_Particles](https://user-images.githubusercontent.com/43366313/201525884-ffb14810-1eb3-45f0-9358-1290f53943f3.gif)<br>*Shooting Particles*

### Character AI

   Enemy AI is setup by creating **behavior trees** and **blackboards**.<br>
   Pathfinding is done by creating a **Navmesh Volume**, which helps bake walking areas for the AI.
   Various features of behavior trees are utlized to give AI more realistic actions, like:
   1. Selectors
   2. Sequences
   3. Tasks
   4. Decorators
   5. Services
      
   **AAIController** class is derived to use functionality like **LineOfSight**.
   **Custom Tasks** to clear blackboard values (BTTask_ClearBlackboardValue), shoot (BTTask_Shoot), along with **custom services** like updating player location (BTService_PlayerLocation, BTService_PlayerLocationIfSeen), alerting (BTService_Alert) are created to provide specific behaviors.

   ![EnemyBehaviorTree](https://user-images.githubusercontent.com/43366313/201524573-37420bed-af28-4256-bd24-2ac634aafd0e.png)<br>*Enemy Behavior Tree*
   
   As per this behavior tree AI is able to patrol, get alerted, follow player, shoot player and search for player in it's last seen position.

### Sound
   
   Sound Effects are played when bullet is fired from gun muzzle by using **UWorld::SpawnSoundAttached** and when bullet hits a surface using **UWorld::PlaySoundAtLocation**.<br>
   Randomization of sound effects is done by creating **SoundCue** assets, for example bullet sfx.
   
   ![SoundCue](https://user-images.githubusercontent.com/43366313/201528209-64e6c3be-cd18-4a7e-8600-7cdfc2075e08.png)<br>*Bullet Hit Sound Cue*

   In order to give spatial effect to sounds an **Attenuation** asset is configured and used with those sounds.
   Environment ambient sound is played by adding an **ambient sound actor** to the map.
   
### UI
   
   UI Widgets in the form of HUD and screens are created to provide information of health, lose or win states. Depending on the win condition the game end screen widget is created and updated from the code, by setting its text and colors.
   ```cpp
   UUserWidget* gameEndScreen = CreateWidget(this, GameEndScreenClass, TEXT("Win Screen UI"));

   if (!gameEndScreen) return;

   UTextBlock* mainText = Cast<UTextBlock>(gameEndScreen->GetWidgetFromName(TEXT("MainText")));
   UTextBlock* secondaryText = Cast<UTextBlock>(gameEndScreen->GetWidgetFromName(TEXT("SecondaryText")));

   if (bIsWinner)
   {
       if (mainText)
       {
           mainText->SetText(WinMainText);
           mainText->SetColorAndOpacity(WinColor);
       }
       if (secondaryText)
       {
           secondaryText->SetText(WinSecondaryText);
           secondaryText->SetColorAndOpacity(WinColor);
       }
   }
   else
   {
       if (mainText)
       {
           mainText->SetText(LossMainText);
           mainText->SetColorAndOpacity(LossColor);
       }
       if (secondaryText)
       {
           secondaryText->SetText(LossSecondaryText);
           secondaryText->SetColorAndOpacity(LossColor);
       }
   }

   gameEndScreen->AddToViewport();
   ```

## Additional Implementation

1. Syncing Animation and movement params
2. Mesh Sockets and Attaching
3. Mesh Bone Hiding
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
