#include "latextemplate.h"


LatexTemplate::LatexTemplate()
{
#ifdef WINHOME
    QString template_path = "G:/Data/Qt/Ebooks/Templates";
#else
    QString template_path = "/media/awegsche/HDD/Qt/Ebooks/Templates";
#endif

    templates = QDir(template_path);


}

