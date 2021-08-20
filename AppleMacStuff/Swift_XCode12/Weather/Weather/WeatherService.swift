//
//  WeatherService.swift
//  Weather
//
//  Created by Krishna Adhikari on 8/17/21.
// Source: https://www.youtube.com/watch?v=DxYAhXLtAB0&t=771s Ale Patron Channel
//    Or Alejandrina Patron Lopez
//

import CoreLocation
import Foundation

public final class WeatherService: NSObject {
    
    private let locationManager = CLLocationManager()
    
    //From https://home.openweathermap.org/api_keys (need to login to my account)
    private let API_KEY = "86a2ba83e2c3685b1b9be30e8bd5b58b"
    //Completion handler that will be executed when we're able to get weather data
    //This is a function - for now this will take no parameter - hence the empty ()
    //And, it will also return no value - hence 'Void', and this is an optional
    // property - hence '?' after the enclosing ')'.
    //We'll modify it later
    //private var completionHandler: (() -> Void)?
    private var completionHandler: ((Weather) -> Void)? //Pass Weather object
    
    //initializer to the class
    public override init() {
        super.init()
        locationManager.delegate = self
    }
    
    //Now let's add functions that get user location and weather data
    public func loadWeatherData(_ completionHandler: @escaping((Weather) -> Void)) {
        self.completionHandler = completionHandler
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
    }
    
    private func makeDataRequest(forCoordinates coordinates: CLLocationCoordinate2D) {
        //API call (copied from: https://openweathermap.org/current Under 'By geographic coordinates'):
        //https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}
        guard let urlString = "https://api.openweathermap.org/data/2.5/weather?lat=\(coordinates.latitude)&lon=\(coordinates.longitude)&appid=\(API_KEY)&units=metric".addingPercentEncoding(withAllowedCharacters: .urlQueryAllowed) else { return }
        guard let url = URL(string: urlString) else { return }
        
        URLSession.shared.dataTask(with: url) { data, response, error in
            guard error == nil, let data = data else { return }
            if let response = try? JSONDecoder().decode(APIResponse.self, from: data) {
                self.completionHandler?(Weather(response: response))
            }
        }.resume()
    }
}

extension WeatherService: CLLocationManagerDelegate {
    public func locationManager( //DidChangeAuthorization(
        _ manager: CLLocationManager,
        didUpdateLocations locations: [CLLocation]
    ) {
        guard let location = locations.first else { return }
        makeDataRequest(forCoordinates: location.coordinate)
    }
    
    public func locationManager(
        _ manager: CLLocationManager,
        didFailWithError error: Error
    ) {
        print("Something went wrong: \(error.localizedDescription)")
    }
}

struct APIResponse: Decodable {
    let name: String
    let main: APIMain
    let weather: [APIWeather]
}

struct APIMain: Decodable {
    let temp: Double
}

struct APIWeather: Decodable {
    let description: String
    let iconName: String
    
    enum CodingKeys: String, CodingKey {
        case description
        case iconName = "main"
    }
}
