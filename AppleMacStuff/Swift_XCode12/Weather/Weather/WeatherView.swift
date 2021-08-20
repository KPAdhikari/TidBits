//
//  ContentView.swift
//  Weather
//
//  Created by Krishna Adhikari on 8/17/21.
//

import SwiftUI

struct WeatherView: View {
    
    @ObservedObject var viewModel: WeatherViewModel
    
    var body: some View {
        //Text("Hello, world!").padding()
        VStack {
            //Text("Los Angeles")
            Text(viewModel.cityName)
                .font(.largeTitle)
                .padding()
            //Text("25°C") //kp: Command+Ctr+Space - type degree, select
            Text(viewModel.temperature) //kp: Command+Ctr+Space - type degree, select
                .font(.system(size: 70))
                .bold()
            //Text("⛅️")
            Text(viewModel.weatherIcon)
                .font(.largeTitle)
                .padding()
            //Text("Clear Sky")
            Text(viewModel.weatherDescription)
        }.onAppear(perform: viewModel.refresh)
    }
}

struct WeatherView_Previews: PreviewProvider {
    static var previews: some View {
        WeatherView(viewModel: WeatherViewModel(weatherService: WeatherService()))
    }
}
