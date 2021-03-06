#include "playlist.h"

PlayList::PlayList()
{
    playListInfo.clear();
    playList = new QMediaPlaylist();
}

QList<SongStorage>* PlayList::getInfo(){
    return &playListInfo;
}

QMediaPlaylist* PlayList::getList(){
    return playList;
}

void PlayList::clear(){
    playList->clear();
    playListInfo.clear();
}

bool PlayList::addMedia(const SongStorage &song){
    if(!song.isValid())
        return false;

    if(!playList->addMedia(song.toMedia()))
        return false;

    playListInfo.push_back(song);
    return true;
}

void PlayList::next()const{
    playList->next();
}

void PlayList::prev()const{
    playList->previous();
}

bool PlayList::isValid()const{
    return playListInfo.size() == playList->mediaCount();
}

bool PlayList::isEmpty()const{
    return playList->isEmpty() && playListInfo.isEmpty();
}

const SongHeader *PlayList::currentHeader()const{
    if(playList->isEmpty() || playList->currentIndex() < 0)
        return nullptr;

    return static_cast<const SongHeader*>(&playListInfo[playList->currentIndex()]);
}

const SongStorage *PlayList::currentSong()const{
    if(playList->isEmpty() || playList->currentIndex() < 0)
        return nullptr;

    return &playListInfo[playList->currentIndex()];
}

int PlayList::size()const{
    return playList->mediaCount();
}

int PlayList::find(const SongHeader &header)const{
    for(int i = 0; i < playList->mediaCount(); ++i) {
        if(header == playList->media(i)) {
            return i;
        }
    }
    return -1;
}

bool PlayList::selectSong(int index){
    if(playList->mediaCount() <= index || index < 0){
        return false;
    }

    playList->setCurrentIndex(index);
    return true;
}

bool PlayList::selectSong(const SongHeader &header){
    return selectSong(find(header));
}



PlayList::~PlayList(){
    delete playList;
}
