##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=FXGHI
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/gabriel/Projects/Fox/FXGHI
ProjectPath            :=/home/gabriel/Projects/Fox/FXGHI
IntermediateDirectory  :=./obj
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Regis Kocicak
Date                   :=15.9.2022
CodeLitePath           :=/home/gabriel/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=bin/debug
OutputFile             :=bin/debug/libFXGHI.so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="FXGHI.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)include $(IncludeSwitch)/opt/foxlib/1.7/74/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)FOX-1.7 $(LibrarySwitch)CHART-1.7 
ArLibs                 :=  "FOX-1.7" "CHART-1.7" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/opt/foxlib/1.7/74/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -fPIC -g -Wall -fexceptions  $(Preprocessors)
CFLAGS   :=  -fPIC -g -Wall -fexceptions  $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_FXGDialogBox.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FXGWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FXWindowController.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FXWindowHeader.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/gabriel/Projects/Fox/FXGHI/.build-debug"
	@echo rebuilt > "/home/gabriel/Projects/Fox/FXGHI/.build-debug/FXGHI"

MakeIntermediateDirs:
	@test -d ./obj || $(MakeDirCommand) ./obj


$(IntermediateDirectory)/.d:
	@test -d ./obj || $(MakeDirCommand) ./obj

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_FXGDialogBox.cpp$(ObjectSuffix): src/FXGDialogBox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FXGDialogBox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FXGDialogBox.cpp$(DependSuffix) -MM src/FXGDialogBox.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gabriel/Projects/Fox/FXGHI/src/FXGDialogBox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FXGDialogBox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FXGDialogBox.cpp$(PreprocessSuffix): src/FXGDialogBox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FXGDialogBox.cpp$(PreprocessSuffix) src/FXGDialogBox.cpp

$(IntermediateDirectory)/src_FXGWindow.cpp$(ObjectSuffix): src/FXGWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FXGWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FXGWindow.cpp$(DependSuffix) -MM src/FXGWindow.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gabriel/Projects/Fox/FXGHI/src/FXGWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FXGWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FXGWindow.cpp$(PreprocessSuffix): src/FXGWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FXGWindow.cpp$(PreprocessSuffix) src/FXGWindow.cpp

$(IntermediateDirectory)/src_FXWindowController.cpp$(ObjectSuffix): src/FXWindowController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FXWindowController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FXWindowController.cpp$(DependSuffix) -MM src/FXWindowController.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gabriel/Projects/Fox/FXGHI/src/FXWindowController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FXWindowController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FXWindowController.cpp$(PreprocessSuffix): src/FXWindowController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FXWindowController.cpp$(PreprocessSuffix) src/FXWindowController.cpp

$(IntermediateDirectory)/src_FXWindowHeader.cpp$(ObjectSuffix): src/FXWindowHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FXWindowHeader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FXWindowHeader.cpp$(DependSuffix) -MM src/FXWindowHeader.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gabriel/Projects/Fox/FXGHI/src/FXWindowHeader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FXWindowHeader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FXWindowHeader.cpp$(PreprocessSuffix): src/FXWindowHeader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FXWindowHeader.cpp$(PreprocessSuffix) src/FXWindowHeader.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./obj/


