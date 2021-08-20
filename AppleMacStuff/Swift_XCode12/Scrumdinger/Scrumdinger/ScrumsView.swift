//
//  ScrumsView.swift .swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/11/21.
//
// Source: https://developer.apple.com/tutorials/app-dev-training/displaying-data-in-a-list

import SwiftUI

struct ScrumsView: View {
    //let scrums: [DailyScrum]
    @Binding var scrums: [DailyScrum]

    var body: some View {
        //Text("Hello, World!")
        //kp: List view
        List {
            //kp: ForEach view
            //ForEach(scrums, id: \.title) { scrum in
            ForEach(scrums) { scrum in
                //NavigationLink(destination: Text(scrum.title)) {
                //NavigationLink(destination: DetailView(scrum: scrum)) {
                NavigationLink(destination: DetailView(scrum: binding(for: scrum))) { 
                    CardView(scrum: scrum)
                }
                .listRowBackground(scrum.color)
            }
        }
        .navigationTitle("Daily Scrums")
        .navigationBarItems(trailing: Button(action: {}) {
                    Image(systemName: "plus")
                })
    }
    private func binding(for scrum: DailyScrum) -> Binding<DailyScrum> {
        guard let scrumIndex = scrums.firstIndex(where: { $0.id == scrum.id }) else {
            fatalError("Can't find scrum in array")
        }
        return $scrums[scrumIndex]
    }
}


struct ScrumsView_Previews: PreviewProvider {
    static var previews: some View {
        NavigationView {
            //ScrumsView(scrums: DailyScrum.data)
            ScrumsView(scrums: .constant(DailyScrum.data))
        }
    }
}
