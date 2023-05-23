#pragma once

using namespace System::Collections::Generic;

public ref class FileManager
{
public:
    System::String^ openedFolderName;

    List<System::String^>^ listOfFiles;

    FileManager() : openedFolderName("") {};

    System::String^ openFolderPromptDialog();

    System::Collections::Generic::List<System::String^>^ getFolderFilesList(System::String^ folderPath);

    System::String^ getAbsolutePathOfFile(System::String^ fileName, System::String^ absoluteFolderPath);

};

