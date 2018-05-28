#include <iostream>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QFile>
#include <QDir>
#include <QRandomGenerator>

#include "virdis_values.h"


int main()
{
    QVector<QColor> colors = get_virdis_values();

    // Step 1: Get the current Directory

    // Step 2: Change into the `2_section` Directory

    // Step 3: Create a `pics` folder/directory if it does not exist

    // Step 4: Remove all old pictures, if any

    // Step 5: Generate 100 pictures and fill with a random QColor
}

