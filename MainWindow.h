#pragma once

#include <msclr\marshal_cppstd.h>
#include <iostream>

#include "NotificationManager.h"
#include "FileManager.h"
#include "AudioManager.h"
#include "ThreadManager.h"
#include "Utils.h"
#include "Logger.h"

namespace AudioEqWin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form, public NotificationObserver
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			addDevices();
			subscribeNotifications();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::ComboBox^ audioDevicesComboBox;
	protected:

	private: System::Windows::Forms::Button^ pauseButton;
	private: System::Windows::Forms::Button^ openButton;
	private: System::Windows::Forms::Label^ filenameLabel;
	private: System::Windows::Forms::TrackBar^ volumeTrackBar;
	private: System::Windows::Forms::Label^ volumeLabel;























	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ musicListBox;
	private: System::Windows::Forms::CheckBox^ resamplingCheckBox;
	private: System::Windows::Forms::Button^ stopButton;
	public: System::Windows::Forms::TrackBar^ timelineTrackBar;















	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->audioDevicesComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->openButton = (gcnew System::Windows::Forms::Button());
			this->filenameLabel = (gcnew System::Windows::Forms::Label());
			this->volumeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->volumeLabel = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->musicListBox = (gcnew System::Windows::Forms::ListBox());
			this->resamplingCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->timelineTrackBar = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeTrackBar))->BeginInit();
			this->flowLayoutPanel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timelineTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(439, 57);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(77, 23);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MainWindow::playButton_Click);
			// 
			// audioDevicesComboBox
			// 
			this->audioDevicesComboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->audioDevicesComboBox->FormattingEnabled = true;
			this->audioDevicesComboBox->Location = System::Drawing::Point(335, 330);
			this->audioDevicesComboBox->Name = L"audioDevicesComboBox";
			this->audioDevicesComboBox->Size = System::Drawing::Size(232, 21);
			this->audioDevicesComboBox->TabIndex = 1;
			this->audioDevicesComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::audioDevicesComboBox_SelectedIndexChanged);
			// 
			// pauseButton
			// 
			this->pauseButton->Location = System::Drawing::Point(439, 87);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(77, 23);
			this->pauseButton->TabIndex = 2;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MainWindow::pauseButton_Click);
			// 
			// openButton
			// 
			this->openButton->Location = System::Drawing::Point(439, 12);
			this->openButton->Name = L"openButton";
			this->openButton->Size = System::Drawing::Size(77, 23);
			this->openButton->TabIndex = 3;
			this->openButton->Text = L"Open";
			this->openButton->UseVisualStyleBackColor = true;
			this->openButton->Click += gcnew System::EventHandler(this, &MainWindow::openButton_Click);
			// 
			// filenameLabel
			// 
			this->filenameLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->filenameLabel->AutoSize = true;
			this->filenameLabel->Location = System::Drawing::Point(6, 338);
			this->filenameLabel->Name = L"filenameLabel";
			this->filenameLabel->Size = System::Drawing::Size(37, 13);
			this->filenameLabel->TabIndex = 4;
			this->filenameLabel->Text = L"No file";
			this->filenameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// volumeTrackBar
			// 
			this->volumeTrackBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->volumeTrackBar->BackColor = System::Drawing::SystemColors::Control;
			this->volumeTrackBar->LargeChange = 10;
			this->volumeTrackBar->Location = System::Drawing::Point(3, 16);
			this->volumeTrackBar->Maximum = 120;
			this->volumeTrackBar->Name = L"volumeTrackBar";
			this->volumeTrackBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->volumeTrackBar->Size = System::Drawing::Size(48, 272);
			this->volumeTrackBar->TabIndex = 1;
			this->volumeTrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->volumeTrackBar->Value = 100;
			this->volumeTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainWindow::volumeTrackBar_ValueChanged);
			// 
			// volumeLabel
			// 
			this->volumeLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->volumeLabel->AutoSize = true;
			this->volumeLabel->Location = System::Drawing::Point(3, 291);
			this->volumeLabel->MinimumSize = System::Drawing::Size(48, 0);
			this->volumeLabel->Name = L"volumeLabel";
			this->volumeLabel->Size = System::Drawing::Size(48, 13);
			this->volumeLabel->TabIndex = 5;
			this->volumeLabel->Text = L"100%";
			this->volumeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// flowLayoutPanel6
			// 
			this->flowLayoutPanel6->Controls->Add(this->label1);
			this->flowLayoutPanel6->Controls->Add(this->volumeTrackBar);
			this->flowLayoutPanel6->Controls->Add(this->volumeLabel);
			this->flowLayoutPanel6->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel6->Location = System::Drawing::Point(522, 2);
			this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			this->flowLayoutPanel6->Size = System::Drawing::Size(55, 317);
			this->flowLayoutPanel6->TabIndex = 8;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->MinimumSize = System::Drawing::Size(48, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Volume";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// musicListBox
			// 
			this->musicListBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->musicListBox->FormattingEnabled = true;
			this->musicListBox->Location = System::Drawing::Point(10, 10);
			this->musicListBox->Name = L"musicListBox";
			this->musicListBox->Size = System::Drawing::Size(410, 247);
			this->musicListBox->TabIndex = 10;
			this->musicListBox->DoubleClick += gcnew System::EventHandler(this, &MainWindow::musicListBox_DoubleClick);
			// 
			// resamplingCheckBox
			// 
			this->resamplingCheckBox->AutoSize = true;
			this->resamplingCheckBox->Location = System::Drawing::Point(435, 145);
			this->resamplingCheckBox->Name = L"resamplingCheckBox";
			this->resamplingCheckBox->Size = System::Drawing::Size(81, 17);
			this->resamplingCheckBox->TabIndex = 11;
			this->resamplingCheckBox->Text = L"Resampling";
			this->resamplingCheckBox->UseVisualStyleBackColor = true;
			this->resamplingCheckBox->Click += gcnew System::EventHandler(this, &MainWindow::resamplingCheckBox_Click);
			// 
			// stopButton
			// 
			this->stopButton->Location = System::Drawing::Point(439, 117);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(75, 23);
			this->stopButton->TabIndex = 12;
			this->stopButton->Text = L"Stop";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MainWindow::stopButton_Click);
			// 
			// timelineTrackBar
			// 
			this->timelineTrackBar->Location = System::Drawing::Point(10, 274);
			this->timelineTrackBar->Maximum = 64;
			this->timelineTrackBar->Name = L"timelineTrackBar";
			this->timelineTrackBar->Size = System::Drawing::Size(410, 45);
			this->timelineTrackBar->TabIndex = 13;
			this->timelineTrackBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->timelineTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainWindow::timelineTrackBar_ValueChanged);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(579, 363);
			this->Controls->Add(this->timelineTrackBar);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->resamplingCheckBox);
			this->Controls->Add(this->musicListBox);
			this->Controls->Add(this->filenameLabel);
			this->Controls->Add(this->audioDevicesComboBox);
			this->Controls->Add(this->flowLayoutPanel6);
			this->Controls->Add(this->openButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->playButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainWindow";
			this->Text = L"AudioEQ";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeTrackBar))->EndInit();
			this->flowLayoutPanel6->ResumeLayout(false);
			this->flowLayoutPanel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timelineTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		void addDevices()
		{
			List<AudioDevice^>^ audioDevicesList = audioManager->getAudioDeviceList();
			int deviceIndex = 0;
			for (deviceIndex = 0; deviceIndex < audioDevicesList->Count; deviceIndex++) {
				this->audioDevicesComboBox->Items->Add(audioDevicesList[deviceIndex]->name);
			}
			if (deviceIndex >= 1)
			{
				this->audioDevicesComboBox->SelectedIndex = 0;
			}
		}

		void subscribeNotifications()
		{
			NotificationManager::Instance->subscribe(this);
		}

		void updateTimeline(int value)
		{
			timelineTrackBar->Value = value;
		}

		void addFiles(String^ folderPath)
		{
			List<String^>^ listOfFiles = fileManager->getFolderFilesList(folderPath);

			for (int i = 0; i < listOfFiles->Count; i++)
			{
				musicListBox->Items->Add((i + 1).ToString() + ". " + listOfFiles[i]);
			}
		}

#pragma region notifications

	public:
		virtual void onNotification(NotificationKey key, void* value) override
		{
			if (key == UPDATE_TIMELINE)
			{
				int sample = (int)value;
				timelineTrackBar->Invoke(gcnew Action<int>(this, &MainWindow::updateTimeline), sample / audioManager->getSampleRate());
			}
		}

#pragma region Definitions
		FileManager^ fileManager = gcnew FileManager();
		AudioManager^ audioManager = gcnew AudioManager();
		DispatchQueue^ threadManager = gcnew DispatchQueue();
#pragma endregion

	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Action^ playAction = gcnew Action(audioManager, &AudioManager::play);
		threadManager->Dispatch(playAction);
	}

	private: System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Action^ stopAction = gcnew Action(audioManager, &AudioManager::pause);
		threadManager->Dispatch(stopAction);
	}

	private: System::Void openButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ folderName = fileManager->openFolderPromptDialog();
		if (folderName == "") return;
		filenameLabel->Text = folderName;
		addFiles(folderName);
	}

	private: System::Void audioDevicesComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		List<AudioDevice^>^ audioDevicesList = audioManager->getAvailableAudioDevicesList();
		AudioDevice^ selectedDevice = audioDevicesList[audioDevicesComboBox->SelectedIndex];
		audioManager->setDefaultAudioDeviceId(selectedDevice->id);
	}

	private: System::Void musicListBox_DoubleClick(System::Object^ sender, System::EventArgs^ e)
	{
		checkIfTrueAndReturn("Index is -1, selected empty obj", musicListBox->SelectedIndex, -1, (std::string)"musicListBox->SelectedIndex");
		checkNullptr(fileManager->openedFolderName, "fileManager->openedFolderName");

		int selectedItemIdx = musicListBox->SelectedIndex;
		String^ selectedFileName;
		if (selectedItemIdx >= 0 && selectedItemIdx < fileManager->listOfFiles->Count)
		{
			selectedFileName = fileManager->listOfFiles[selectedItemIdx];
		}
		checkNullptr(selectedFileName, "selectedFileName");

		String^ absolutePath = fileManager->getAbsolutePathOfFile(selectedFileName, fileManager->openedFolderName);
		checkNullptr(absolutePath, "absolutePath");

		audioManager->terminate();
		bool isSuccess = audioManager->openFile(absolutePath);
		if (isSuccess)
		{
			int numOfSamples = audioManager->getNumOfAudioSamples();
			timelineTrackBar->Value = 0;
			timelineTrackBar->Maximum = (numOfSamples / audioManager->getSampleRate());
		}
	}

	private: System::Void volumeTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		volumeLabel->Text = Convert::ToString(volumeTrackBar->Value) + "%";
		audioManager->setVolume((float)volumeTrackBar->Value / 100);
	}

	private: System::Void resamplingCheckBox_Click(System::Object^ sender, System::EventArgs^ e)
	{
		audioManager->useResampling = resamplingCheckBox->Checked;
	}

	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		audioManager->terminate();
	}

	private: System::Void timelineTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		audioManager->setTimeTo(timelineTrackBar->Value);
	}
	};
}