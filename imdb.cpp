#include <iterator>
#include <string>
#include <vector>
#include <unordered_map>

#include "imdb.h"


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

    movie m(movie_name, movie_id, timestamp, categories, director_name, actor_ids);
    std::pair<std::string, movie> elem(movie_id, m);
    movies.insert(elem);

    for (i = 0; i < actor_ids.size(); ++i) {
        if (actors[i].debut_year > timestamp) {
            actors[i].debut_year = timestamp;
        }
        if (actors[i].last_year < timestamp) {
            actors[i].last_year = timestamp;
        }
        actors[i].years = actors[i].last_year - 
                          actors[i].debut_year;
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
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].add_rating(user_id, rating);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].update_rating(user_id, rating);
    }
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].remove_rating(user_id, rating);
    }
}

std::string IMDb::get_rating(std::string movie_id) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        double rating;
        std::string final_rating;
        int temp_rating = (int)(movies[movie_id].get_rating() * 1000);
        if (temp_rating % 10 >= 5) {
            temp_rating += 10;
            temp_rating /= 10;
            rating = (double)temp_rating / 100.0;
            final_rating = to_string(rating);
            return final_rating;
        }
    }
    if (movies[movie_id].no_rating()) {
        return "none";
    }
}

std::string IMDb::get_longest_career_actor() {
    return "";
}

std::string IMDb::get_most_influential_director() {
    return "";
}

std::string IMDb::get_best_year_for_category(std::string category) {
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
    return "";
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
    return "";
}
