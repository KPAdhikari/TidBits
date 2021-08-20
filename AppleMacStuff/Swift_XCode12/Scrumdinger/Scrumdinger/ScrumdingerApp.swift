//
//  ScrumdingerApp.swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/9/21.
//

import SwiftUI

@main
struct ScrumdingerApp: App {
    @State private var scrums = DailyScrum.data
    var body: some Scene {
        WindowGroup {
            NavigationView {
                //MeetingView()
                //ScrumsView(scrums: DailyScrum.data) //After Chap 3, Section 2
                ScrumsView(scrums: $scrums)
            }
        }
    }
}
