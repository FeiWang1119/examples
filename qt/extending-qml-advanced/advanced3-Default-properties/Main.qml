// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import People

BirthdayParty {
    host: Boy {
        name: "Bob Jones"
        shoeSize: 12
    }
// The guests property can be designated as the default property of BirthdayParty.
// Meaning that each object created inside of a BirthdayParty is implicitly appended to the default property guests.
    Boy { name: "Leo Hodges" }
    Boy { name: "Jack Smith" }
    Girl { name: "Anne Brown" }
}
