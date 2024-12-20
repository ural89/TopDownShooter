# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /home/ural/Linux_Unreal_Engine_5.3.2
GAMEPROJECTFILE =/home/ural/Documents/GitHub/TopDownShooter/TopDownShooter.uproject

TARGETS = \
	TopDownShooter-Linux-DebugGame  \
	TopDownShooter-Linux-Shipping  \
	TopDownShooter \
	TopDownShooterEditor-Linux-DebugGame  \
	TopDownShooterEditor-Linux-Shipping  \
	TopDownShooterEditor \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend TopDownShooterEditor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug TopDownShooterEditor-Linux-Debug


TopDownShooter-Linux-DebugGame:
	 $(PROJECTBUILD) TopDownShooter Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

TopDownShooter-Linux-Shipping:
	 $(PROJECTBUILD) TopDownShooter Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

TopDownShooter:
	 $(PROJECTBUILD) TopDownShooter Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

TopDownShooterEditor-Linux-DebugGame:
	 $(PROJECTBUILD) TopDownShooterEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

TopDownShooterEditor-Linux-Shipping:
	 $(PROJECTBUILD) TopDownShooterEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

TopDownShooterEditor:
	 $(PROJECTBUILD) TopDownShooterEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)
