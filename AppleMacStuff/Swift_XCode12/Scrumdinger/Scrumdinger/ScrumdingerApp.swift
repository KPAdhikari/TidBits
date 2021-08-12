//
//  ScrumdingerApp.swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/9/21.
//

import SwiftUI

@main
struct ScrumdingerApp: App {
    var body: some Scene {
        WindowGroup {
            //MeetingView()
            ScrumsView(scrums: DailyScrum.data) //After Chap 3, Section 2
        }
    }
}
