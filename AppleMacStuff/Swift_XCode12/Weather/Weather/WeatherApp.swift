//
//  WeatherApp.swift
//  Weather
//
//  Created by Krishna Adhikari on 8/17/21.
//

import SwiftUI

@main
struct WeatherApp: App {
    var body: some Scene {
        WindowGroup {
            let weatherService = WeatherService()
            let viewModel = WeatherViewModel(weatherService: weatherService)
            //WeatherView()
            WeatherView(viewModel: viewModel)
        }
    }
}
