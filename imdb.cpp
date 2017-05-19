#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>

#include "include/imdb.h"


IMDb::IMDb() {
    // initialize what you need here.
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp, // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids) {

    // Adaugare film in baza de date;
    movie m(movie_name, movie_id, timestamp, categories, director_name,
            actor_ids);
    std::pair<std::string, movie> elem(movie_id, m);
    movies.insert(elem);
    recent_movies.insert(m);


    // Caut directorul in baza de date
    auto found_director = directors.find(director_name);

    if (found_director == directors.end()) {
        std::pair<std::string, director> elem(director_name, director(director_name));
        found_director = directors.insert(elem).first;
    }

    for (unsigned int i = 0; i < actor_ids.size(); ++i) {
        // Se adauga sau se actualizeaza datele despre un actor;
        actor &current_actor = actors[actor_ids[i]];
        int &debut_year = current_actor.get_debut_year();
        int &last_year = current_actor.get_last_year();
        int &years = current_actor.get_years();

        if (debut_year > timestamp) {
            debut_year = timestamp;
        }

        if (last_year < timestamp) {
            last_year = timestamp;
        }

        years = last_year - debut_year;
        if (max_years < current_actor || max_years.get_id() == "") {
            max_years = current_actor;
        }

        if (!found_director->second.check_collaboration(actor_ids[i])) {
            found_director->second.add_collaboration(actor_ids[i]);
        }
    }

    if (max_coll < found_director->second) {
        max_coll = found_director->second;
    }
}

void IMDb::add_user(std::string user_id, std::string name) {
    std::pair<std::string, std::string> user(user_id, name);
    users.insert(user);
}

void IMDb::add_actor(std::string actor_id, std::string name) {
    actor new_actor(actor_id, name);
    std::pair<std::string, actor> elem(actor_id, new_actor);
    actors.insert(elem);
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating) {
    // Curat cache-ul
    cache.clear();
    double old_rating = movies[movie_id].add_rating(user_id, rating);
    if (movies[movie_id].nr_ratings() == 1) {
        rated_movies.insert(movies[movie_id]);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating) {
    // Curat cache-ul
    cache.clear();
    double old_rating = movies[movie_id].update_rating(user_id, rating);
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
    // Curat cache-ul
    cache.clear();
    double old_rating = movies[movie_id].remove_rating(user_id);
    if (movies[movie_id].nr_ratings() == 0) {
        rated_movies.erase(movies[movie_id]);
    }
}

std::string IMDb::get_rating(std::string movie_id) {
    // Am pus conditia de fara rating la inceput
    // Nu ai tratat cazul de rotunjire pt %10 < 5
    // Am scos operatiile ce se repeta din if
    if (movies.find(movie_id) != movies.end()) {
        if (!movies[movie_id].nr_ratings()) {
            return NONE;
        }

        double rating;
        std::string final_rating;
        std::stringstream stream;
        int temp_rating = (int)(movies[movie_id].get_rating() * 1000);

        if (temp_rating % 10 >= 5) {
            temp_rating += 10;
        }

        temp_rating /= 10;
        rating = (double)temp_rating / 100.0;
        stream << std::fixed << std::setprecision(2) << rating;
        final_rating = stream.str();
        return final_rating;
    }

    return NONE;
}

std::string IMDb::get_longest_career_actor() {
    if (max_years.get_id() != "") {
        return max_years.get_id();
    }
    return NONE;
}

std::string IMDb::get_most_influential_director() {
    if (max_coll.director_name != "") {
        return max_coll.director_name;
    }
    return NONE;
}

std::string IMDb::get_best_year_for_category(std::string category) {
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
    if (!recent_movies.empty()) {
        int i = 1;
        auto it = recent_movies.rbegin();
        std::string result = it->get_movie_id();
        ++it;
        for (it = it; i < k && it != recent_movies.rend(); ++it, ++i) {

            result += " " + it->get_movie_id();
        }
        return result;
    }

    return NONE;
}

std::string IMDb::get_top_k_actor_pairs(int k) {
    return "";
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k) {
    return "";
}

std::string IMDb::get_avg_rating_in_range(int start, int end) {
    double rating = 0.0;
    int number_of_ratings = 0;
    movie m_begin(start);
    movie m_end(end);
    auto lower = rated_movies.lower_bound(m_begin);
    auto upper = rated_movies.upper_bound(m_end);
    int lower_time = lower->get_timestamp();
    int upper_time = upper->get_timestamp();
    
    if (cache.find(lower_time) != cache.end()) {
        if (cache[lower_time].find(upper_time) != cache[lower_time].end()) {
            return cache[lower_time][upper_time];
        }
    }

    if (lower == upper) {
        cache[lower_time][upper_time] = NONE;
        return NONE;   
    }

    for (auto it = lower; it != upper; ++it) {
        std::string movie_id = it->get_movie_id();
        rating += movies[movie_id].get_rating();
        ++number_of_ratings;
    }

    rating /= number_of_ratings;
    std::stringstream stream;
    std::string result;

    stream << std::fixed << std::setprecision(2) << rating;
    result = stream.str();

    cache[lower_time][upper_time] = result;
    return result;

}
