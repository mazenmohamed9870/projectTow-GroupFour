#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
// ========== ENUMERATIONS ========== //
// [Kareem] Define department and room type enumerations
enum Department
{
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

// [Kareem] Define room type enumerations
enum RoomType
{
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== PATIENT CLASS ========== //
// [Malak Soliman] Patient class definition and implementation
class Patient
{
private:
    int id;
    string name;
    int age;
    string contact;
    stack<string> medicalHistory;
    queue<string> testQueue;
    bool isAdmitted;
    RoomType roomType;

public:
    Patient(int pid, string n, int a, string c);

    void admitPatient(RoomType type);
    void dischargePatient();
    void addMedicalRecord(string record);
    void requestTest(string testName);
    string performTest();
    void displayHistory();

    int getId();
    string getName();
    bool getAdmissionStatus();
};

// [Malak Soliman] Patient constructor implementation
Patient::Patient(int pid, string n, int a, string c)
{
    id = pid;
    name = n;
    age = a;
    contact = c;
    isAdmitted = false;
}

// [Malak Soliman] Admit patient to hospital
void Patient::admitPatient(RoomType type)
{
    isAdmitted = true;
    roomType = type;
    addMedicalRecord("Patient admitted to " + to_string(type) + " room type.");
}

// [Malak Soliman] Discharge patient from hospital
void Patient::dischargePatient()
{
    isAdmitted = false;
    addMedicalRecord("Patient discharged.");
}

// [Malak Soliman] Add medical record to patient history
void Patient::addMedicalRecord(string record)
{
    medicalHistory.push(record);
}

// [Malak Soliman] Request a medical test
void Patient::requestTest(string testName)
{
    testQueue.push(testName);
    addMedicalRecord("Test requested: " + testName);
}

// [Malak Soliman] Perform the next test in queue
string Patient::performTest()
{
    if (testQueue.empty())
    {
        return "No tests pending";
    }
    string testName = testQueue.front();
    testQueue.pop();
    addMedicalRecord("Test performed: " + testName);
    return testName;
}

// [Malak Soliman] Display patient medical history
void Patient::displayHistory()
{
    cout << "Medical History for " << name << ":" << endl;
    stack<string> tempStack;

    // Reverse the stack to show recent first
    while (!medicalHistory.empty())
    {
        tempStack.push(medicalHistory.top());
        medicalHistory.pop();
    }

    while (!tempStack.empty())
    {
        cout << "- " << tempStack.top() << endl;
        medicalHistory.push(tempStack.top());
        tempStack.pop();
    }
}

// [Malak Soliman] Get patient ID
int Patient::getId()
{
    return id;
}

// [Malak Soliman] Get patient name
string Patient::getName()
{
    return name;
}

// [Malak Soliman] Get admission status
bool Patient::getAdmissionStatus()
{
    return isAdmitted;
}

// ========== DOCTOR CLASS ========== //
// [Hanna] Doctor class definition and implementation
class Doctor
{
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;

public:
    Doctor(int did, string n, Department d);

    void addAppointment(int patientId);
    int seePatient();

    int getId();
    string getName();
    string getDepartment();
};

// [Hanna] Doctor constructor implementation
Doctor::Doctor(int did, string n, Department d)
{
    id = did;
    name = n;
    department = d;
}

// [Hanna] Add appointment to doctor's queue
void Doctor::addAppointment(int patientId)
{
    appointmentQueue.push(patientId);
}

// [Hanna] See next patient in queue
int Doctor::seePatient()
{
    if (appointmentQueue.empty())
    {
        return -1;
    }
    int patientId = appointmentQueue.front();
    appointmentQueue.pop();
    return patientId;
}

// [Hanna] Get doctor ID
int Doctor::getId()
{
    return id;
}

// [Hanna] Get doctor name
string Doctor::getName()
{
    return name;
}

// [Hanna] Get department name as string
string Doctor::getDepartment()
{
    switch (department)
    {
    case CARDIOLOGY:
        return "Cardiology";
    case NEUROLOGY:
        return "Neurology";
    case ORTHOPEDICS:
        return "Orthopedics";
    case PEDIATRICS:
        return "Pediatrics";
    case EMERGENCY:
        return "Emergency";
    case GENERAL:
        return "General";
    default:
        return "Unknown";
    }
}

// ========== HOSPITAL CLASS ========== //
// [Mazen Mohamed] Hospital class definition and implementation
class Hospital
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    queue<int> emergencyQueue;
    int patientCounter;
    int doctorCounter;

public:
    Hospital();

    int registerPatient(string name, int age, string contact);
    int addDoctor(string name, Department dept);
    void admitPatient(int patientId, RoomType type);
    void addEmergency(int patientId);
    int handleEmergency();
    void bookAppointment(int doctorId, int patientId);
    void displayPatientInfo(int patientId);
    void displayDoctorInfo(int doctorId);
};

// [Mazen Mohamed] Hospital constructor implementation
Hospital::Hospital()
{
    patientCounter = 1;
    doctorCounter = 1;
}

// [Mazen Mohamed] Register a new patient
int Hospital::registerPatient(string name, int age, string contact)
{
    Patient newPatient(patientCounter, name, age, contact);
    patients.push_back(newPatient);
    return patientCounter++;
}

// [Mazen Mohamed] Add a new doctor
int Hospital::addDoctor(string name, Department dept)
{
    Doctor newDoctor(doctorCounter, name, dept);
    doctors.push_back(newDoctor);
    return doctorCounter++;
}

// [Mazen Mohamed] Admit a patient
void Hospital::admitPatient(int patientId, RoomType type)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            patient.admitPatient(type);
            return;
        }
    }
    cout << "Patient with ID " << patientId << " not found." << endl;
}

// [Mazen Mohamed] Add emergency case
void Hospital::addEmergency(int patientId)
{
    emergencyQueue.push(patientId);
}

// [Mazen Mohamed] Handle emergency case
int Hospital::handleEmergency()
{
    if (emergencyQueue.empty())
    {
        cout << "No emergencies in queue." << endl;
        return -1;
    }
    int nextEmergency = emergencyQueue.front();
    emergencyQueue.pop();
    return nextEmergency;
}

// [Mazen Mohamed] Book appointment
void Hospital::bookAppointment(int doctorId, int patientId)
{
    for (auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            doctor.addAppointment(patientId);

            // Log appointment in patient's medical history
            for (auto &patient : patients)
            {
                if (patient.getId() == patientId)
                {
                    patient.addMedicalRecord("Appointment booked with Doctor ID: " + to_string(doctorId));
                    return;
                }
            }
            cout << "Patient with ID " << patientId << " not found." << endl;
            return;
        }
    }
    cout << "Doctor with ID " << doctorId << " not found." << endl;
}

// [Mazen Mohamed] Display patient information
void Hospital::displayPatientInfo(int patientId)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            cout << "Patient ID: " << patient.getId() << endl;
            cout << "Name: " << patient.getName() << endl;
            cout << "Admission Status: " << (patient.getAdmissionStatus() ? "Admitted" : "Not Admitted") << endl;
            patient.displayHistory();
            return;
        }
    }
    cout << "Patient with ID " << patientId << " not found." << endl;
}

// [Mazen Mohamed] Display doctor information
void Hospital::displayDoctorInfo(int doctorId)
{
    for (auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            cout << "Doctor ID: " << doctor.getId() << endl;
            cout << "Name: " << doctor.getName() << endl;
            cout << "Department: " << doctor.getDepartment() << endl;
            return;
        }
    }
    cout << "Doctor with ID " << doctorId << " not found." << endl;
}

// ========== MAIN PROGRAM ========== //
// [Kareem] Main function implementation
int main()
{
    Hospital hospital;

    // Test Case 1: Registering patients
    int p1 = hospital.registerPatient("John Doe", 35, "555-1234");
    int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");

    // Test Case 2: Adding doctors
    int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY);
    int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);

    // Test Case 3: Admitting patients
    hospital.admitPatient(p1, PRIVATE_ROOM);
    hospital.admitPatient(p2, ICU);
    // Try admitting already admitted patient
    hospital.admitPatient(p1, SEMI_PRIVATE);

    // Test Case 4: Booking appointments
    hospital.bookAppointment(d1, p1);
    hospital.bookAppointment(d1, p2);
    hospital.bookAppointment(d2, p3);
    // Try booking with invalid doctor/patient
    hospital.bookAppointment(999, p1); // Invalid doctor
    hospital.bookAppointment(d1, 999); // Invalid patient

    // Test Case 5: Handling medical tests
    // These would normally be called on Patient objects
    // In a real implementation, we'd need a way to access patients

    // Test Case 6: Emergency cases
    hospital.addEmergency(p3);
    hospital.addEmergency(p1);
    int emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency(); // No more emergencies

    // Test Case 7: Discharging patients
    // Would normally call dischargePatient() on Patient objects

    // Test Case 8: Displaying information
    hospital.displayPatientInfo(p1);
    hospital.displayPatientInfo(p2);
    hospital.displayPatientInfo(999); // Invalid patient

    hospital.displayDoctorInfo(d1);
    hospital.displayDoctorInfo(d2);
    hospital.displayDoctorInfo(999); // Invalid doctor

    // Test Case 9: Doctor seeing patients
    // These would normally be called on Doctor objects
    // In a real implementation, we'd need a way to access doctors

    // Test Case 10: Edge cases
    Hospital emptyHospital;
    emptyHospital.displayPatientInfo(1); // No patients
    emptyHospital.displayDoctorInfo(1);  // No doctors
    emptyHospital.handleEmergency();     // No emergencies

    return 0;
}