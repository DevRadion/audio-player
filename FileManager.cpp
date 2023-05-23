#include "FileManager.h"
#include "Utils.h"
#include "Logger.h"
#include <msclr\marshal_cppstd.h>
#include <string>
#include <filesystem>

using namespace System::Windows::Forms;

System::String^ FileManager::openFolderPromptDialog()
{
    FolderBrowserDialog^ folderBrowserDialog = gcnew FolderBrowserDialog();
    folderBrowserDialog->ShowNewFolderButton = false;

    System::String^ selectedFolder = gcnew System::String("");

    if (folderBrowserDialog->ShowDialog() == DialogResult::OK)
    {
        selectedFolder = gcnew System::String(msclr::interop::marshal_as<std::string>(folderBrowserDialog->SelectedPath).c_str());
        openedFolderName = selectedFolder;
    }

    return selectedFolder;
}

List<System::String^>^ FileManager::getFolderFilesList(System::String^ folderPath)
{
    List<System::String^>^ listOfFiles = gcnew List<System::String^>;
    std::string stdStringFolderPath = msclr::interop::marshal_as<std::string>(folderPath);
    for (const auto& entry : std::filesystem::directory_iterator(stdStringFolderPath))
    {
        std::filesystem::path fileName = entry.path().filename();
        std::string fileExt = fileName.extension().u8string();

        if (fileExt == ".wav")
        {
            listOfFiles->Add(gcnew System::String(fileName.c_str()));
        }   
    }

    this->listOfFiles = listOfFiles;

    return listOfFiles;
}

System::String^ FileManager::getAbsolutePathOfFile(System::String^ fileName, System::String^ absoluteFolderPath)
{
    return absoluteFolderPath + "\\" + fileName;
}