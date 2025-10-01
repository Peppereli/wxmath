//Name: Ehsan Behnia
//Task: Practical Work 3
//Checked by: Dinara Kozhamzharova
//Date of completion: 23.02.2025

//To compile: "g++ `wx-config --cppflags --libs`"
//To run: "./a.out"

//Include wxWidgets library
#include<wx/wx.h>
#include<cmath>

//Class for App (essential for the window to open in the first place)
class App : public wxApp
{
public:
    bool OnInit();
};

//Class for the Frame (window)
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
private:
    void OnButtonClicked1(wxCommandEvent& evt);
    void OnButtonClicked2(wxCommandEvent& evt);
    void OnButtonClicked3(wxCommandEvent& evt);
    void OnButtonClicked4(wxCommandEvent& evt);
    int gcd(int a, int b);
    int ext_gcd(int a, int b, int &x, int &y);
    int mod_red(double m, double n);
    long mod_inverse(int a, int b);
    wxTextCtrl* integer1;
    wxTextCtrl* integer2;
};

//Necessary functions for calculating the necessary tasks
int MainFrame::mod_red(double m, double n){
    int q = floor(m/n);
    int r = m-q*n;
    return r;
}
int MainFrame::ext_gcd(int a, int b, int &x, int &y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    int x1, y1;
    int d=ext_gcd(b, a%b, x1, y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}

int MainFrame::gcd(int a, int b){
    if (b==0){
        return a;
    }
    return gcd(b, a%b);
}

long MainFrame::mod_inverse(int a, int m){
    if (gcd(a, m)!=1){
        return -1;
    }
    int x, y;
    ext_gcd(a, m, x, y);
    x=(x%m+m)%m;
    return x;
}

//Display of controls (buttons, input text) and binding them to their respective functions with dynamic event handling
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title){
    wxPanel* panel = new wxPanel(this);

    wxButton* button1 = new wxButton(panel, wxID_ANY, "GCD", wxPoint(300, 75), wxSize(200, 50));

    wxButton* button2 = new wxButton(panel, wxID_ANY, "EXT. GCD", wxPoint(300, 150), wxSize(200, 50));

    wxButton* button3 = new wxButton(panel, wxID_ANY, "MOD. REDUCTION", wxPoint(300, 225), wxSize(200, 50));

    wxButton* button4 = new wxButton(panel, wxID_ANY, "MOD. INVERSE", wxPoint(300, 300), wxSize(200, 50));

    integer1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint (300, 375), wxSize(200, -1));

    integer2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 425), wxSize(200, -1));

    //Dynamic event handling
    button1->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked1, this);
    button2->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked2, this);
    button3->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked3, this);
    button4->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked4, this);

    //StatusBar works like the console in JavaScript, appears at the bottom of the window and displays messages
    CreateStatusBar();
}

//First button event (GCD)
void MainFrame::OnButtonClicked1(wxCommandEvent& evt){
    wxString IntValue1 = integer1->GetValue();
    wxString IntValue2 = integer2->GetValue();
    long num1, num2;
    //Convert input text to numbers
    if (IntValue1.ToLong(&num1) && IntValue2.ToLong(&num2)){
        wxLogStatus("%ld and %ld", num1, num2);
    }else{
        wxLogStatus("Invalid");
    }
    int g = abs(gcd(num1, num2));
    
    //LogMessage makes the output pop up in a seperate window
    wxLogMessage("GCD: %d", g);
}

//Second button event (EXT_GCD)
void MainFrame::OnButtonClicked2(wxCommandEvent& evt){
    wxString IntValue1 = integer1->GetValue();
    wxString IntValue2 = integer2->GetValue();
    long num1, num2;
    if (IntValue1.ToLong(&num1) && IntValue2.ToLong(&num2)){
        wxLogStatus("%ld and %ld", num1, num2);
    }else{
        wxLogStatus("Invalid");
        
    }
    int x, y;
    int d = ext_gcd(num1, num2, x, y);

    wxLogMessage("EXT_GCD: %d, %d, %d", abs(d), x, y);
}

//Third button event (MOD. REDUCTION)
void MainFrame::OnButtonClicked3(wxCommandEvent& evt){
    wxString IntValue1 = integer1->GetValue();
    wxString IntValue2 = integer2->GetValue();
    double num1, num2;
    if (IntValue1.ToDouble(&num1) && IntValue2.ToDouble(&num2)){
        wxLogStatus("%f and %f", num1, num2);
    }else{
        wxLogStatus("Invalid");
    }
    int r = mod_red(num1, num2);
    int con = num2;

    wxLogMessage("MOD. REDUCTION: %dmod%d", r, con);
}

//Fourth button event (MOD. INVERSE)
void MainFrame::OnButtonClicked4(wxCommandEvent& evt){
    wxString IntValue1 = integer1->GetValue();
    wxString IntValue2 = integer2->GetValue();
    long num1, num2;
    if (IntValue1.ToLong(&num1) && IntValue2.ToLong(&num2)){
        wxLogStatus("%ld and %ld", num1, num2);
    }else{
        wxLogStatus("Invalid");
    }
    long i = mod_inverse(num1, num2);
    wxLogMessage("MOD. INVERSE: %ld", i);
}

//App implementation
wxIMPLEMENT_APP(App);

//bool OnInit has to be true for the window to remain open
bool App::OnInit(){
    MainFrame* mainFrame = new MainFrame("Math stuff");
    mainFrame->SetClientSize(800, 600); //Window opens with this size
    mainFrame->Center(); //Window is centered on the display
    mainFrame->Show(); //Show() the main frame (mind blown!)
    return true;
}

//Thank you for checking all of my code.
